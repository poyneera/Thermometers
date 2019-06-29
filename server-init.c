#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	
	FILE * fid = fopen("front_temps.csv","w");
	fprintf(fid,"Date (DD/MM/YY),Time (HH:MM:SS),Temp (deg F),RH (\%)\r\n");
	fclose(fid);
	
	fid = fopen("all_temps.csv","w");
	fprintf(fid,"Date (DD/MM/YY),Time (HH:MM),Front Temp (deg F),Front RH (\%),Back Temp (deg F),Back RH (\%)\r\n");
	fclose(fid);
	
	return 0;
}