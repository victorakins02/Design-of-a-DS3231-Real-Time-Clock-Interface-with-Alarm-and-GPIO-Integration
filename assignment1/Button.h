#include <gpiod.h>
#include <string>

class Button {
private:
    unsigned int pin;
    struct gpiod_line_request *request;
public:
    Button(unsigned int pinNumber);
    bool isPressed();
    ~Button();
};
