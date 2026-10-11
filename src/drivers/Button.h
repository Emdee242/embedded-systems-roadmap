#ifndef BUTTON_H
#define BUTTON_H
#include <Arduino.h>
class Button{
private:
const uint8_t pin;
public:
Button (uint8_t x);
void begin() const;
bool readPin () const;
};
#endif