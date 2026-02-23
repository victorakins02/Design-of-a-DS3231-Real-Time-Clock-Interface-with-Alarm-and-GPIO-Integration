#ifndef LED_H
#define LED_H

#include <gpiod.h>

class LED {
private:
    struct gpiod_chip *chip;
    struct gpiod_line_request *request;
    unsigned int pin;

public:
    LED(int gpioNumber);
    void turnOn();
    void turnOff();
    ~LED();
};

#endif
