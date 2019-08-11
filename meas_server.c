#include <wiringPi.h>
#include <stdio.h>
#include <wiringPiI2C.h>
#include <unistd.h>
#include "temp_util.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

int main(void){

	int dev, temp, hum;
	float temperature, rh;
	struct sockaddr_in servaddr;
	struct sockaddr clientaddr;
	char buf[100];
	FILE *fid;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int blen = sizeof(buf);
	int status = 0;
	int csize = sizeof(clientaddr);
	int cid, sid = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);

	dev = mySetup();

	hum = myRead(dev,HUM_NH);
	temp = myRead(dev,PR_TMP);

	temperature = tempProc(temp);
	rh = humProc(hum);

	fid = fopen("front_temps.csv","a");
	fprintf(fid,"%2d/%2d/%4d,%2d:%2d,%2.0f,%2.0f\r\n",tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900,tm.tm_hour,tm.tm_min,temperature,rh);
	fclose(fid);

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(31950);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sid,(struct sockaddr *) &servaddr,sizeof(servaddr))<0){
		printf("Error binding socket: %d\n", errno);
		return -1;
	}

	status = listen(sid,10);
	if(status < 0){
		printf("Error listening: %d\n",errno);
		return -1;
	}

	cid = accept(sid,&clientaddr,&csize);

	recv(cid,buf,blen,0);
	close(sid);
	close(cid);

	fid = fopen("all_temps.csv","a");
	fprintf(fid,"%2d/%2d/%4d,%2d:%2d,%2.0f,%2.0f,%s\r\n",tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900,tm.tm_hour,tm.tm_min,temperature,rh,buf);
	fclose(fid);

	return 0;
}
