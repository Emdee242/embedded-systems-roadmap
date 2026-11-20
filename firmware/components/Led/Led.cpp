#include "Led.h"
#include "drivers/gpio.h"
Led::Led(uint8_t x) : pin(x), mask(1ULL << pin) {}
void Led::off() {
    gpio_set_level(mask, 0);
    isOn = false;
}
void Led::on() {
    gpio_set_level(mask, 1);
    isOn = true;
}
void Led::begin() const {
    gpio_config_t LedConfig{};
    LedConfig.intr_type = GPIO_INTR_DISABLE;
    LedConfig.mode = GPIO_MODE_OUTPUT;
    LedConfig.pin_bit_mask = mask;
    LedConfig.pull_down_en = GPIO_PULLDOWN_DISABLE;
    LedConfig.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&LedConfig);
    }
