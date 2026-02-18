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

   // Getter function for seconds
   unsigned int DS3231::getSeconds(){
	unsigned char* hex_sec = this->readRegisters(1, 0x00);

	if (hex_sec == NULL) {
	   return 0;
	}

	unsigned int bin_sec = bcdToDec(hex_sec[0]);

	delete[] hex_sec;

	return bin_sec;
   }

   // Destructor
   DS3231::~DS3231(){}

}
