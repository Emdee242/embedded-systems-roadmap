#ifndef SENSORTASK_H
#define SENSORTASK_H
#include "../../drivers/Mpu6500.h"
#include "../../core/CircularBuffer.h"
#include "../../core/Debouncer.h"
#include "../../core/SoftwareTimer.h"
#include "../../drivers/Button.h"
#include "../Application.h"
#include <Arduino.h>
#include <optional>
struct SensorTaskParam{
Mpu6500 *mpu;
CircularBuffer *AccelBuffer;
CircularBuffer *GyroBuffer;
Debouncer *debounce;
SoftwareTimer *timer;
Button *button;
CurrentState *state;
std::optional<AccelerometerReading> *Accelerometer;
std::optional<GyroscopeReading> *Gyroscope;
};
#endif