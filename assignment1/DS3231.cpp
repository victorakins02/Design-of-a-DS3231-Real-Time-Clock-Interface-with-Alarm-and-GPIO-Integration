/*
 * DS3231.cpp 
 * Copyright (c) 2025 Derek Molloy (www.derekmolloy.ie)
 * Modified by: Student Name
 */

#include "DS3231.h"
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <stdio.h>

using namespace std;

namespace een1071 {

   // Your solution implementation here
   DS3231::DS3231(unsigned int bus, unsigned int device) : I2CDevice(bus, device) {}

   // Mainly needed to get 2 rows e.g temp
   unsigned char* DS3231::readDevice(unsigned int address){
	return this->readRegisters(2, address);
   }

   // Convert from BCD to Binary (mainly for seconds for now)
   int DS3231::bcdToDec(unsigned char bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
   }

   // Getter Function for Temperature
   float DS3231::getTemperature(){
	unsigned char* hex_temp = this->readRegisters(2, 0x11);

	if (hex_temp == NULL){
	   return 0;
	}

	float MSB_temp = (float)((signed char)hex_temp[0]);
	float LSB_temp = (float)(hex_temp[1] >> 6) * 0.25f;

	float temp = MSB_temp + LSB_temp;

	delete[] hex_temp;

	return temp;
   }

   unsigned int DS3231::getHours(){
	unsigned char* bcd_hour = this->readRegisters(1, 0x02);

	if (bcd_hour == NULL){
	   return 0;
	}

 	unsigned int bin_hour = bcdToDec(bcd_hour[0] & 0x3F);

	delete[] bcd_hour;

	return bin_hour;
   }

   unsigned int DS3231::getMinutes(){
	unsigned char* bcd_min = this->readRegisters(1, 0x01);

	if (bcd_min == NULL){
	   return 0;
	}

	unsigned int bin_min = bcdToDec(bcd_min[0]);

	delete[] bcd_min;

	return bin_min;
   }

   // Getter function for seconds
   unsigned int DS3231::getSeconds(){
	unsigned char* bcd_sec = this->readRegisters(1, 0x00);

	if (bcd_sec == NULL) {
	   return 0;
	}

	unsigned int bin_sec = bcdToDec(bcd_sec[0]);

	delete[] bcd_sec;

	return bin_sec;
   }

   

   // Destructor
   DS3231::~DS3231(){}

}
