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
#include "Button.h"
using namespace std;
using namespace een1071;

int main() {

    // Your application code here

    // Objects
    LED myLED(17);
    DS3231 rtc(1, 0x68);
    Button snoozeButton(22);

    // Set Date/Time
    rtc.setTime(12, 0, 0);
    rtc.setDate(2, 24, 2, 26);

    // Set Alarm
    rtc.activateAlarm(true, false);
    rtc.setAlarm1(12, 0, 15);
    myLED.turnOn(); // LED On to show alarm on

   while(true) {
    if (rtc.alarm1Triggered()) {
        cout << "ALARM TRIGGERED!" << endl;
        
        // Loop here until the button is pressed
        while (!snoozeButton.isPressed()) {
            myLED.flashOn(); // Keep flashing while waiting for the user
            usleep(100000);  // Flash speed
        }

        // --- Everything below happens ONLY after the button is pressed ---
        cout << "Snooze button detected!" << endl;
        
        // 1. Calculate new time (Your rollover logic here)
        int h = rtc.getHours();
	int m = rtc.getMinutes();
	int s = rtc.getSeconds();

	s += 10;
            if (s >= 60) {
                s -= 60;
                m += 1;
            }
            if (m >= 60) {
                m = 0;
                h = (h + 1) % 24;
            }

        // 2. Update Hardware
        rtc.setAlarm1(h, m, s);
        rtc.clearAlarm1();
        
        myLED.turnOff();
        cout << "Snoozed! New alarm set for: " << h << ":" << m << ":" << s << endl;

        // 3. Wait for user to let go of the button
        while (snoozeButton.isPressed()) { 
            usleep(10000); 
        } 
    }
    usleep(100000); // Main loop heartbeat
}

    cout << "DS3231 RTC Code for Assignment 1 EEN1071" << endl;
    return 0;
}
