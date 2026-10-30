#ifndef SENSORTASK_H
#define SENSORTASK_H
#include "../../drivers/Mpu6500.h"
#include <Arduino.h>
#include <Wire.h>
#include <optional>
class SensorTask{
private:
    Mpu6500 CoreMPU{Wire};
    std::optional<AccelerometerReading> Accelerometer;
    std::optional<GyroscopeReading> Gyroscope;
public:
static void sensorTaskEntry(void *parameters);
void start();
};
#endif