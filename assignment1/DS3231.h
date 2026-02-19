/*
 * DS3231.h
 * Copyright (c) 2025 Derek Molloy (www.derekmolloy.ie)
 * Modified by: Student Name
 */

#ifndef DS3231_H_
#define DS3231_H_
#include"I2CDevice.h"

namespace een1071 {

class DS3231:public I2CDevice{
// Your C++ code here
private:
	int bcdToDec(unsigned char bcd);

public:
	DS3231(unsigned int bus, unsigned int device);
	unsigned char* readDevice(unsigned int address);
	float getTemperature();
	unsigned int getHours();
	unsigned int getMinutes();
	unsigned int getSeconds();
	void getTime();
	unsigned int getDay();
	unsigned int getDate();
	unsigned int getMonth();
	unsigned int getYear();
	void getToday();
	virtual ~DS3231();
};

} /* namespace een1071 */

#endif
