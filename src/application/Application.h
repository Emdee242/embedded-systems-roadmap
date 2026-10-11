#ifndef "APPLICATION_H"
#define "APPLICATION_H"
#include "../drivers/Button.h"
#include "../core/Debouncer.h"
#include "../core/CircularBuffer.h"
#include "../core/SoftwareTimer.h"
#include "../drivers/Mpu6500.h"
#include <Wire.h>
#include <optional>
class Application{
private:
Button CoreButton(7);
Debouncer CoreDebouncer(CoreButton);
CircularBuffer AccelBuffer;
CircularBuffer GyroBuffer;
SoftwareTimer CoreTimer;
Mpu6500 CoreMPU(Wire);
std::optional<AccelerometerReading> Accelerometer;
std::optional<GyroscopeReading> Gyroscope;
public:
void start();
void update();
};
#endif