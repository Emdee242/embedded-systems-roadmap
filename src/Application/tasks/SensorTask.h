#ifndef SENSORTASK_H
#define SENSORTASK_H
#include "../../drivers/Mpu6500.h"
#include "../../core/CircularBuffer.h"
#include "../../core/Debouncer.h"
#include "../../core/SoftwareTimer.h"
#include "../../core/Logger.h"
#include "../../drivers/Button.h"
#include <Arduino.h>
#include <optional>
enum class CurrentState { IDLE, ACTIVE };
struct SensorTaskParam{
Mpu6500 *mpu;
CircularBuffer *AccelBuffer;
CircularBuffer *GyroBuffer;
Debouncer *debounce;
SoftwareTimer *timer;
Button *button;
CurrentState state = CurrentState::IDLE;
std::optional<AccelerometerReading> *Accelerometer;
std::optional<GyroscopeReading> *Gyroscope;
QueueHandle_t sensorHandle;
Logger SensorLogger;
};
struct SensorVariables{
    float ax;
    float ay;
    float az;
    float gx;
    float gy;
    float gz;
};
struct QueueTask{
CurrentState QueueMessage;
SensorVariables QueueVariables;
};
void sensorTaskEntry(void *parameters);
#endif