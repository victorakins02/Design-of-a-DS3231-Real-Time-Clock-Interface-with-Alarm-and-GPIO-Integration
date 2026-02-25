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
      if (rtc.alarm1Triggered()){
         cout << "ALARM TRIGGERED!" << endl;
         for(int i = 0; i < 3; i++) {
                myLED.flashOn();
            }
      if (snoozeButton.isPressed()) {
            cout << "Snooze button detected!" << endl;

            // Get current time
            int h = rtc.getHours();
            int m = rtc.getMinutes();
            int s = rtc.getSeconds();

            // Add 10 seconds with rollover logic
            s += 10;
            if (s >= 60) {
                s -= 60;
                m += 1;
            }
            if (m >= 60) {
                m = 0;
                h = (h + 1) % 24;
            }

            // Set the new alarm time
            rtc.setAlarm1(h, m, s);

            // Clear the hardware flag and reset LED states
            rtc.clearAlarm1();
            myLED.turnOff();
            myLED.turnOn();

            cout << "Snoozed! New alarm set for: " << h << ":" << m << ":" << s << endl;

            // Debounce delay to prevent multiple triggers from one press
            usleep(250000); 
        }
      }
   }

    cout << "DS3231 RTC Code for Assignment 1 EEN1071" << endl;
    return 0;
}
