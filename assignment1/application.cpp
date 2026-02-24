/*
 * Application.cpp
 * Copyright (c) 2025 Derek Molloy (www.derekmolloy.ie)
 * Modified by: Student Name
 */

#include <iostream>
#include "DS3231.h"
#include <unistd.h>
#include <pthread.h>
#include "LED.h"

using namespace std;
using namespace een1071;

int main() {

    // Your application code here
    LED myLED(17);

    een1071::DS3231 rtc(1, 0x68);
    rtc.setTime(11, 30, 0);
    rtc.setDate(4, 19, 2, 26);
    rtc.setAlarm1(11, 30, 10);
    myLED.turnOn();
    rtc.activateAlarm(true, false);
    // Testing getter functions
    while (true) {
    	float temp = rtc.getTemperature();

	rtc.getToday();
	unsigned int day = rtc.getDay();
	rtc.getTime();
	cout << "Temperature: " << temp << endl;
	cout << endl;
	if (rtc.alarm1Triggered() || rtc.alarm2Triggered()){
	   cout << "Alarm went off!" << endl;
	   for(int i = 0; i < 5; i++){
	      myLED.flashOn();
	   }
    	   myLED.turnOff();
	}
	sleep(1);

	}
    cout << "DS3231 RTC Code for Assignment 1 EEN1071" << endl;
    return 0;
}
