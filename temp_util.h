#include <wiringPi.h>
#include <stdio.h>
#include <wiringPiI2C.h>
#include <unistd.h>

#ifndef _TEMP_UTIL
#define _TEMP_UTIL

#define ADDR   0x40
#define HUM_H  0xE5 // Humidity with hold
#define HUM_NH 0xF5 // Humidity no hold
#define TMP_H  0xE3 // Temp with hold 
#define TMP_NH 0xF3 // Temp no hold 
#define PR_TMP 0xE0 // Temp from previous Humidity
#define RESET  0xFE // RESET command
#define RHT_RD 0xE7 // Read some particular register

int mySetup();

int myRead(int devid, int cmd);

float tempProc(int raw);
float humProc(int raw);

#endif