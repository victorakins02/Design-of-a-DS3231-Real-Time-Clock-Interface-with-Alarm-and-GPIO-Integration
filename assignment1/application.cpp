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

    // 2. Call your readDevice for the Temperature register (0x11)
    unsigned char* data = rtc.readDevice(0x11);

    if (data != NULL) {
        // 3. Print the two bytes in Hexadecimal format
        std::cout << "Raw Register 0x11 (MSB): 0x" << std::hex << (int)data[0] << std::endl;
        std::cout << "Raw Register 0x12 (LSB): 0x" << std::hex << (int)data[1] << std::endl;
        
        // Don't forget to delete the data afterward to prevent memory leaks!
        delete[] data; 
    } else {
        std::cout << "Failed to read from the device!" << std::endl;
    }
	cout << "DS3231 RTC Code for Assignment 1 EEN1071" << endl;
	return 0;
}
