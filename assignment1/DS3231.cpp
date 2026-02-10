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
   unsigned char* DS3231::readDevice(unsigned int address){
	return this->readRegisters(2, address);
   }

   DS3231::~DS3231(){
	
   }

}
