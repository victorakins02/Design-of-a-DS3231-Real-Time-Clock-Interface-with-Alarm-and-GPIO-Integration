/*
 * Application.cpp
 * Copyright (c) 2025 Derek Molloy (www.derekmolloy.ie)
 * Modified by: Student Name
 */

#include <iostream>
#include "DS3231.h"
#include <unistd.h>
#include <pthread.h>

using namespace std;
using namespace een1071;

int main() {

    // Your application code here
    een1071::DS3231 rtc(1, 0x68);
    // Testing getter functions
    while (true) {
    	float temp = rtc.getTemperature();
	unsigned int hours = rtc.getHours();
        unsigned int mins = rtc.getMinutes();
    	unsigned int seconds = rtc.getSeconds();

	cout << "Time: " << hours << ":" << mins << ":" << seconds << endl;
	cout << "Temperature: " << temp << endl;

	sleep(1);

	}
    cout << "DS3231 RTC Code for Assignment 1 EEN1071" << endl;
    return 0;
}
