#include "SoftwareTimer.h"
#include <Arduino.h>
#include <cassert>
void SoftwareTimer::reset() { recordTime = millis(); }
void SoftwareTimer::setTimer(unsigned long x) { intervalTime = x; }
bool SoftwareTimer::intervalPassed() {
    bool result = false;
    assert(recordTime != 0 && "machine time(recordTime) should not be zero");
    assert(intervalTime != 0 && "interval should not be zero");
    if ((millis() - recordTime) >= intervalTime) {
        recordTime += intervalTime;
        result = true;
    }
    return result;
}