#include "Button.h"
#include <iostream>
#include <gpiod.h>

Button::Button(unsigned int pinNumber) : pin(pinNumber) {
    const char *chipname = "gpiochip0"; // RP1 on Pi 5
    struct gpiod_chip *chip;
    struct gpiod_line_settings *settings;
    struct gpiod_line_config *line_cfg;

    // 1. Open the chip
    chip = gpiod_chip_open("/dev/gpiochip0");
    if (!chip) {
        std::cerr << "Failed to open chip" << std::endl;
        return;
    }

    // 2. Create line settings for INPUT
    settings = gpiod_line_settings_new();
    gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_INPUT);

    // 3. Create line configuration
    line_cfg = gpiod_line_config_new();
    gpiod_line_config_add_line_settings(line_cfg, &pin, 1, settings);

    // 4. Request the line
    request = gpiod_chip_request_lines(chip, nullptr, line_cfg);

    // Clean up temporary setup objects
    gpiod_line_config_free(line_cfg);
    gpiod_line_settings_free(settings);
    gpiod_chip_close(chip);
}

Button::~Button() {
    if (request) {
        gpiod_line_request_release(request);
    }
}

bool Button::isPressed() {
    if (!request) return false;

    // Read the value (returns 1 for Active/High, 0 for Inactive/Low)
    enum gpiod_line_value value = gpiod_line_request_get_value(request, pin);
    
    // With Pull-down: 1 means the button is pressed (connected to 3.3V)
    return (value == GPIOD_LINE_VALUE_ACTIVE);
}
