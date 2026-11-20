#ifndef LED_H
#define LED_H
#include <cstdint>
#include "driver/gpio.h"
class Led {
  private:
    const gpio_num_t pin;
    const uint64_t mask;
    bool isOn = false;

  public:
    explicit Led(uint8_t x);
    void on();
    void off();
    void begin() const;
    int getPin() const { return pin; }
    bool ledState() const { return isOn; }
};
#endif