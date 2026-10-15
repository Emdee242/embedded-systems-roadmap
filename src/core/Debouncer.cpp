#include "Debouncer.h"
#include "../drivers/Button.h"
#include <Arduino.h>
Debouncer::Debouncer(const Button& btn) : refButton(btn){};
void Debouncer::update() {
    initialState = officialState;
    bool tempReadState = refButton.readPin();
    if (lastRawRead != tempReadState) {
        changeDetect = millis();
    }
    if ((millis() - changeDetect) >= refBounceTime) {
        officialState = tempReadState;
    } else {
    }
    lastRawRead = tempReadState;
}
bool Debouncer::fall() {
    bool triggered = false;
    if (initialState == HIGH && officialState == LOW) {
        triggered = true;
    }
    return triggered;
}
bool Debouncer::lift() {
    bool triggered = false;
    if (initialState == LOW && officialState == HIGH) {
        triggered = true;
    }
    return triggered;
}