#include <wiringPi.h>
#include <stdio.h>
#include <wiringPiI2C.h>
#include <unistd.h>
#include "temp_util.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>

int main(void){
	
	int dev, temp, hum;
	float temperature, rh;
	char buf[100];
	char ip[20];
	int n, sockid, stat;
	int blen;
	struct sockaddr_in saddr;
	FILE *fid;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	dev = mySetup();
	
	hum = myRead(dev,HUM_NH);
	temp = myRead(dev,PR_TMP);
	
	temperature = tempProc(temp);
	rh = humProc(hum);
	
	fid = fopen("back_temps.csv","a");
	fprintf(fid,"%d/%d/%d,%d:%d,%4.2f,%4.2f\r\n",tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900,tm.tm_hour,tm.tm_min,temperature,rh);
	fclose(fid);
	
	sprintf(buf,"%4.2f,%4.2f",temperature,rh);
	blen = sizeof(buf);
	
	sockid = socket(AF_INET,SOCK_STREAM,0);

	if (sockid < 0){
		printf("Error! %d",errno);
		return -1;
	}

	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(31950);
	saddr.sin_addr.s_addr = inet_addr("192.168.1.102");

	stat = connect(sockid,(struct sockaddr *) &saddr,sizeof(saddr));

	if (stat < 0){
		printf("Error! %d",errno);
		return -1;
	}
	
	stat = send(sockid,buf,blen,0);
	
	close(sockid);
	
	return 0;

}