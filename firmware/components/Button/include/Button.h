#ifndef BUTTON_H
#define BUTTON_H
#include <cstdint>
#include "driver/gpio.h"
class Button {
  private:
    const gpio_num_t pin;
    const uint64_t mask;
  public:
    explicit Button(uint8_t x);
    void begin() const;
    bool readPin() const;
};
#endif