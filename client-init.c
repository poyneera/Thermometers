#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	
	FILE * fid = fopen("back_temps.csv","w");
	fprintf(fid,"Date (DD/MM/YY),Time (HH:MM:SS),Temp (deg F),RH (\%)\r\n");
	fclose(fid);
	
	return 0;
}