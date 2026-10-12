#ifndef APPLICATION_H
#define APPLICATION_H
#include "../drivers/Button.h"
#include "../core/Debouncer.h"
#include "../core/CircularBuffer.h"
#include "../drivers/Mpu6500.h"
#include "../core/SoftwareTimer.h"
#include <Wire.h>
#include <optional>
enum class CurrentState{
IDLE,
ACTIVE
};
class Application{
private:
const uint8_t buttonPin = 7;
Button CoreButton{buttonPin};
Debouncer CoreDebouncer{CoreButton};
CircularBuffer AccelBuffer;
CircularBuffer GyroBuffer;
Mpu6500 CoreMPU{Wire};
SoftwareTimer CoreTimer;
std::optional<AccelerometerReading> Accelerometer;
std::optional<GyroscopeReading> Gyroscope;
CurrentState ApplicationState = CurrentState::IDLE;
unsigned long readInterval = 1000;
public:
void start();
void update();
};
#endif