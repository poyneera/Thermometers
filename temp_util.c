#include <wiringPi.h>
#include <stdio.h>
#include <wiringPiI2C.h>
#include <unistd.h>
#include "temp_util.h"

int mySetup(){
	int dev,temp;
	dev = wiringPiI2CSetup(0x40);
	temp = wiringPiI2CWrite(dev,RESET);
	temp = wiringPiI2CReadReg8(dev,RHT_RD);
	usleep(50000);
	return dev;
}

int myRead(int dev, int cmd){
	int out,chk;
	long start;
	wiringPiI2CWrite(dev,cmd);
	start = millis();
	while(millis() - start < 1000){
		int tmp = wiringPiI2CRead(dev);
		if (tmp > 0) {
			out = tmp << 8 | wiringPiI2CRead(dev);
			chk = wiringPiI2CRead(dev);
			return out;
		}
		usleep(6000);
	}
	return -1;
}

float tempProc(int raw){
	float out = raw;
	out *= 175.72;
	out /= 65536;
	out -=46.85;
	out *= 1.8;
	out += 32;
	return out;
}


float humProc(int raw){
	float out = raw;
	out *= 125;
	out /= 65536;
	out -= 6;
	return out;
}
