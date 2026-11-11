#include "Mpu6500.h"
#include <Wire.h>
#include <optional>
Mpu6500 FirstMPU(Wire);
std::optional<AccelerometerReading> Accelerometer;
std::optional<GyroscopeReading> Gyroscope;
Result someResult;
Logger someLog;
float ax;
float ay;
float az;
float gx;
float gy;
float gz;
void setup() {
  FirstMPU.firstLog.setLimit(Severity::INFO);
  Wire.begin();
  Serial.begin(115200);
  someResult = FirstMPU.begin();
  FirstMPU.sleep(0);
  FirstMPU.cycle(0);
  FirstMPU.configAccel(0, 0);
  FirstMPU.configGyro(0, 0);
}
void loop() {
      if (someResult == Result::TOO_MANY_BYTES) {
        someLog.Log("Data is too long", Severity::ERROR);
    } else if (someResult == Result::INVALID_SENSOR) {
        someLog.Log("Invalid device address", Severity::ERROR);
    } else if (someResult == Result::INVALID_REG) {
        someLog.Log("Invalid register address", Severity::ERROR);
    } else if (someResult == Result::ERROR) {
        someLog.Log("Unrecognized error", Severity::ERROR);
    } else if (someResult == Result::TIMEOUT) {
        someLog.Log("Timeout", Severity::ERROR);
    } else {
        someLog.Log("non-existing return type, check current endTransmission "
                     "documentation", Severity::ERROR);
    }
  /*if (Accelerometer = FirstMPU.measureAccel(); Accelerometer) {
    Accelerometer->get(ax, ay, az);
    Serial.print("Accelerometer:       ");
    Serial.print(ax);
    Serial.print("       ");
    Serial.print(ay);
    Serial.print("       ");
    Serial.println(az);
  }
  if (Gyroscope = FirstMPU.measureGyro(); Gyroscope) {
    Gyroscope->get(gx, gy, gz);
    Serial.print("Gyroscope:           ");
    Serial.print(gx);
    Serial.print("       ");
    Serial.print(gy);
    Serial.print("       ");
    Serial.println(gz);
  }
  delay(500);
  */
}