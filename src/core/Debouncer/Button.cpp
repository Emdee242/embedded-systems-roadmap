#include "Button.h"
#include <Arduino.h>
Button::Button (uint8_t x) : pin(x){};
void Button::begin() const{
  pinMode(pin, INPUT_PULLUP);
}
bool Button::readPin () const{
  return digitalRead(pin);
}