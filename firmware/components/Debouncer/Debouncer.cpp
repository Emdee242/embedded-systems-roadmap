#include "include/Debouncer.h"
#include "Button.h"
#include <cassert>
#include "esp_timer.h"
Debouncer::Debouncer(const Button& btn) : refButton(btn){};
void Debouncer::setBounceTime(unsigned long x) {
    refBounceTime = x;
    assert(refBounceTime > minDebounceTime && refBounceTime < maxDebounceTime);
}
void Debouncer::update() {
    initialState = officialState;
    bool tempReadState = refButton.readPin();
    if (lastRawRead != tempReadState) {
        changeDetect = esp_timer_get_time();
    }
    if ((esp_timer_get_time() - changeDetect) >= refBounceTime) {
        officialState = tempReadState;
    }
    lastRawRead = tempReadState;
}
bool Debouncer::fall() {
    bool triggered = false;
    if (initialState == true && officialState == false) {
        triggered = true;
    }
    return triggered;
}
bool Debouncer::lift() {
    bool triggered = false;
    if (initialState == false && officialState == true) {
        triggered = true;
    }
    return triggered;
}