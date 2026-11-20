#include "include/SoftwareTimer.h"
#include <cassert>
#include "esp_timer.h"
void SoftwareTimer::reset() { recordTime = esp_timer_get_time(); }
void SoftwareTimer::setTimer(unsigned long x) { intervalTime = x; }
bool SoftwareTimer::intervalPassed() {
    bool result = false;
    assert(recordTime != 0 && "machine time(recordTime) should not be zero");
    assert(intervalTime != 0 && "interval should not be zero");
    if ((esp_timer_get_time() - recordTime) >= intervalTime) {
        recordTime += intervalTime;
        result = true;
    }
    return result;
}