#include "include/Button.h"
#include "driver/gpio.h"
Button::Button(uint8_t x) : pin(x), mask(1ULL << pin){};
void Button::begin() const {
    gpio_config_t ButtonConfig = {};
    ButtonConfig.intr_type = GPIO_INTR_DISABLE;
    ButtonConfig.mode = GPIO_MODE_INPUT;
    ButtonConfig.pin_bit_mask = mask;
    ButtonConfig.pull_down_en = GPIO_PULLDOWN_ENABLE;
    ButtonConfig.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&ButtonConfig);
    }
bool Button::readPin() const { return gpio_get_level(mask); }