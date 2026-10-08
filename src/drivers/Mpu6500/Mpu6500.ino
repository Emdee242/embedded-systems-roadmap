#include "Mpu6500.h"
#include <Wire.h>
#include <optional>
Mpu6500 FirstMPU(Wire);
std::optional<AccelerometerReading> Accelerometer;
std::optional<GyroscopeReading> Gyroscope;
int16_t ax;
int16_t ay;
int16_t az;
int16_t gx;
int16_t gy;
int16_t gz;
int check = true;
void setup() {
  FirstMPU.firstLog.setLimit(Severity::INFO);
  Wire.begin();
  Serial.begin(115200);
  FirstMPU.begin();
  FirstMPU.sleep(0);
  FirstMPU.cycle(0);
  FirstMPU.configAccel(0, 0);
  FirstMPU.configGyro(0, 0);
}
void loop() {
  if (check) {
    Serial.println("Successful");
  } else {
    Serial.println("Unsuccessful");
  };
  if (Accelerometer = FirstMPU.measureAccel(); Accelerometer) {
    Accelerometer->get(ax, ay, az);
    Serial.print("Accelerometer:       ");
    Serial.print(static_cast<double>(ax) / 16384);
    Serial.print("       ");
    Serial.print(static_cast<double>(ay) / 16384);
    Serial.print("       ");
    Serial.println(static_cast<double>(az) / 16384);
  }
  if (Gyroscope = FirstMPU.measureGyro(); Gyroscope) {
    Gyroscope->get(gx, gy, gz);
    Serial.print("Gyroscope:           ");
    Serial.print((static_cast<double>(gx) / 131) + 1.9);
    Serial.print("       ");
    Serial.print((static_cast<double>(gy) / 131) - 2.5);
    Serial.print("       ");
    Serial.println((static_cast<double>(gz) / 131) + 1.3);
  }
  delay(500);
}