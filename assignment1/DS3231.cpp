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

   // Convert from BCD to Decimal (mainly for getting time)
   int DS3231::bcdToDec(unsigned char bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
   }

   // Convert from Decimal to BCD (mainly used to set time)
   unsigned char DS3231::DecTobcd(int val) {
    return (unsigned char)( (val / 10 << 4) | (val % 10) );
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
   // Getter function for Hours
   unsigned int DS3231::getHours(){
	unsigned char* bcd_hour = this->readRegisters(1, 0x02);

	if (bcd_hour == NULL){
	   return 0;
	}

 	unsigned int bin_hour = bcdToDec(bcd_hour[0] & 0x3F);

	delete[] bcd_hour;

	return bin_hour;
   }

   // Getter Function to get minutes
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

   void DS3231::getTime(){
	unsigned int hours = this->getHours();
        unsigned int mins = this->getMinutes();
    	unsigned int seconds = this->getSeconds();

	cout << "Time: " << hours << ":" << mins << ":" << seconds << endl;
   }

   unsigned int DS3231::getDay(){
	unsigned char* bcd_day = this->readRegisters(1, 0x03);

	if (bcd_day == NULL) {
	   return 0;
	}

	unsigned int bin_day = bcd_day[0];

	switch (bin_day) {
	   case 1:
		cout << "Monday" << endl;
		break;
	   case 2:
		cout << "Tuesday" << endl;
		break;
	   case 3:
                cout << "Wednesday" << endl;
                break;
	   case 4:
		cout << "Thursday" << endl;
		break;
	   case 5:
		cout << "Friday" << endl;
		break;
	   case 6:
		cout << "Saturday" << endl;
		break;
	   case 7:
		cout << "Sunday" << endl;
		break;
	   default:
		cout << "Invalid Day" << endl;
		break;
	}

	delete[] bcd_day;

	return bin_day;
  }

   unsigned int DS3231::getDate(){
	unsigned char* bcd_date = this->readRegisters(1, 0x04);

	if (bcd_date == NULL){
	   return 0;
	}

	unsigned int bin_date = bcdToDec(bcd_date[0]);

	delete[] bcd_date;

	return bin_date;

   }

  unsigned int DS3231::getMonth(){
	unsigned char* bcd_month = this->readRegisters(1, 0x05);

	if (bcd_month == NULL) {
	   return 0;
	}

	unsigned int bin_month = bcdToDec(bcd_month[0]);

	delete[] bcd_month;

	return bin_month;
   }

   unsigned int DS3231::getYear(){
	unsigned char* bcd_year = this->readRegisters(1, 0x06);

	if (bcd_year == NULL) {
	   return 0;
	}

	unsigned int bin_year = bcdToDec(bcd_year[0]);

	delete[] bcd_year;

	return bin_year;
  }

   void DS3231::getToday() {
	unsigned int date = this->getDate();
	unsigned int month = this->getMonth();
	unsigned int year = this->getYear();

	cout << "Date: " << date << "/" << month << "/" << year << endl;

   }

   // Set time functions
   void DS3231::setSeconds(int seconds){
	unsigned char bcd_secs = DecTobcd(seconds);

	this->writeRegister(0x00, bcd_secs);
   }

   void DS3231::setMinutes(int minutes){
	unsigned char bcd_mins = DecTobcd(minutes);

	this->writeRegister(0x01, bcd_mins);
   }


   void DS3231::setHours(int hours) {
	unsigned char bcd_hrs = DecTobcd(hours);

	this->writeRegister(0x02, bcd_hrs);
   }

   void DS3231::setTime(int hours, int minutes, int seconds){
	this->setHours(hours);
	this->setMinutes(minutes);
	this->setSeconds(seconds);
   }

   // Set Date Functions
   void DS3231::setDay(int day){
	unsigned char bcd_day = DecTobcd(day);
	this->writeRegister(0x03, bcd_day);
   }

   void DS3231::setDateOfMonth(int date){
	unsigned char bcd_date = DecTobcd(date);
	this->writeRegister(0x04, bcd_date);
   }

   void DS3231::setMonth(int month){
	unsigned char bcd_month = DecTobcd(month);
	this->writeRegister(0x05, bcd_month);
   }

   void DS3231::setYear(int year){
	unsigned char bcd_year = DecTobcd(year);
	this->writeRegister(0x06, bcd_year);
   }

   void DS3231::setDate(int day, int date, int month, int year){
	this->setDay(day);
	this->setDateOfMonth(date);
	this->setMonth(month);
	this->setYear(year);
   }

   void DS3231::setAlarm1(int hour, int minutes, int seconds){
	unsigned char bcd_hour = DecTobcd(hour);
	unsigned char bcd_minutes = DecTobcd(minutes);
	unsigned char bcd_seconds = DecTobcd(seconds);

	this->writeRegister(0x07, bcd_seconds);
	this->writeRegister(0x08, bcd_minutes);
	this->writeRegister(0x09, bcd_hour);
	this->writeRegister(0x0A, 0x80);
   }

    void DS3231::setAlarm2(int hour, int minutes){
        unsigned char bcd_hour = DecTobcd(hour);
        unsigned char bcd_minutes = DecTobcd(minutes);

        this->writeRegister(0x0B, bcd_minutes);
        this->writeRegister(0x0C, bcd_hour);
        this->writeRegister(0x0D, 0x80);
   }

   void DS3231::activateAlarm(bool alarm1, bool alarm2){
	unsigned char control = 0x04;
	if (alarm1) {
	   control |= 0x01;
	}

	if (alarm2) {
	   control |= 0x02;
	}

	this->writeRegister(0x0E, control);
   }

   bool DS3231::alarm1Triggered(){
	unsigned char* status = this->readRegisters(1, 0x0F);

	if (status == NULL) {
	   return false;
	}

	bool isTriggered = (status[0] & 0x01);

	if (isTriggered) {
	    this->writeRegister(0x0F, status[0] & ~0x01);
	}

	delete[] status;

	return isTriggered;
   }

    bool DS3231::alarm2Triggered(){
        unsigned char* status = this->readRegisters(1, 0x0F);

        if (status == NULL) {
           return false;
        }

        bool isTriggered = (status[0] & 0x02);

        if (isTriggered) {
            this->writeRegister(0x0F, status[0] & ~0x02);
        }

        delete[] status;

        return isTriggered;
   }

   // Sqaure Wave
   void DS3231::activateSquareWave(bool enable, SQW_FREQ freq){
   	unsigned char control = readRegister(0x0E);

    	control &= 0xE3;

    	if (enable) {
           control |= (freq << 3);
    	}
	else {
           control |= 0x04;
    	}

    	writeRegister(0x0E, control);
   }

   // Destructor
   DS3231::~DS3231(){}

}
