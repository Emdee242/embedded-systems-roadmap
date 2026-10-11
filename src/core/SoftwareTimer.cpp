#include "SoftwareTimer.h"
#include <Arduino.h>
void SoftwareTimer::reset() {
  recordTime = millis();
}
void SoftwareTimer::setTimer(unsigned long x) {
  intervalTime = x;
}
bool SoftwareTimer::intervalPassed() {
  bool result = false;
  if ((millis() - recordTime) >= intervalTime) {
    recordTime += intervalTime;
    result = true;
  }
  return result;
}