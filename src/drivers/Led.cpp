#include "Led.h"
#include <Arduino.h>
Led::Led(int x) : pin(x){}
void Led::off(){
  digitalWrite(pin, LOW);
  isOn = false;
}
void Led::on(){
  digitalWrite(pin, HIGH);
  isOn = true;
}
void Led::begin() const{
  pinMode(pin, OUTPUT);
}
