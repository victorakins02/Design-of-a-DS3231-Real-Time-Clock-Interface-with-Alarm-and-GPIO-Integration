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
	unsigned char DecTobcd (int decimal);
public:
	DS3231(unsigned int bus, unsigned int device);
	unsigned char* readDevice(unsigned int address);
	// Get Temperature Functions
	float getTemperature();

	// Get Time Functions
	unsigned int getHours();
	unsigned int getMinutes();
	unsigned int getSeconds();
	void getTime();

	// Get Date Functions
	unsigned int getDay();
	unsigned int getDate();
	unsigned int getMonth();
	unsigned int getYear();
	void getToday();

	// Set Time functions
	void setSeconds(int seconds);
	void setMinutes(int minutes);
	void setHours(int hour);
	void setTime(int hour , int minutes, int seconds);

	// Set Date functions
	void setDay(int Today);
	void setDateOfMonth(int date);
	void setMonth(int month);
	void setYear(int Year);
	void setDate(int day, int date, int month, int year);

	// Set Alarms
	void setAlarm1(int hours, int minutes, int seconds);
	void setAlarm2(int hours, int minutes);
	void activateAlarm(bool alarm1, bool alarm2);
	bool alarm1Triggered();
	bool alarm2Triggered();
	virtual ~DS3231();
};

} /* namespace een1071 */

#endif
