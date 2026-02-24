#include "LED.h"
#include <iostream>
#include <unistd.h>

LED::LED(int gpioNumber) {
    this->pin = gpioNumber;

    chip = gpiod_chip_open("/dev/gpiochip0");

    // Create Output
    struct gpiod_line_settings *settings = gpiod_line_settings_new();
    gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_OUTPUT);

    // Link to Pin
    struct gpiod_line_config *line_cfg = gpiod_line_config_new();
    gpiod_line_config_add_line_settings(line_cfg, &pin, 1, settings);

    // Reserve Pin
    request = gpiod_chip_request_lines(chip, NULL, line_cfg);

    gpiod_line_settings_free(settings);
    gpiod_line_config_free(line_cfg);
}

// Turn the LED on (3.3V)
void LED::turnOn() {
   if (request) {
	gpiod_line_request_set_value(request, pin, GPIOD_LINE_VALUE_ACTIVE);
   }
}

void LED::flashOn(){
   if (request) {
	gpiod_line_request_set_value(request, pin, GPIOD_LINE_VALUE_ACTIVE);

        usleep(200000);

        gpiod_line_request_set_value(request, pin, GPIOD_LINE_VALUE_INACTIVE);

        usleep(200000);
   }
}

// Turn the LED off (0.0V)
void LED::turnOff() {
   if (request) {
	gpiod_line_request_set_value(request, pin, GPIOD_LINE_VALUE_INACTIVE);
   }
}

// Destructor
LED::~LED() {
    if (request) {
        gpiod_line_request_set_value(request, pin, GPIOD_LINE_VALUE_INACTIVE);
        gpiod_line_request_release(request);
    }
    if (chip) {
	gpiod_chip_close(chip);
    }
}

