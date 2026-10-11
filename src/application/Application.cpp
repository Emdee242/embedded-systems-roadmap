#include "Application.h"
#include "../drivers/Button.h"
#include "../core/Debouncer.h"
#include "../core/CircularBuffer.h"
#include "../core/SoftwareTimer.h"
#include "../drivers/Mpu6500.h"
#include <Wire.h>
#include <optional>
void Application::start(){
  Wire.begin();
  Serial.begin(115200);
  CoreButton.begin();
  CoreTimer.setTimer();
  CoreTimer.reset();
  CoreMPU.begin();
  CoreMPU.sleep(0);
  CoreMPU.cycle(0);
  CoreMPU.configAccel(0, 0);
  CoreMPU.configGyro(0, 0);
  CoreMPU.firstLog.setLimit(Severity::INFO);
}
void Application::update(){
float ax;
float ay;
float az;
float gx;
float gy;
float gz;
CoreDebouncer.update();
if(CoreDebouncer.fall()){
  if (Accelerometer = CoreMPU.measureAccel(); Accelerometer) {
    Accelerometer->get(ax, ay, az);
    Serial.print("Accelerometer:       ");
    Serial.print(ax);
    AccelBuffer.write(ax);
    Serial.print("       ");
    Serial.print(ay);
    AccelBuffer.write(ay);
    Serial.print("       ");
    Serial.println(az);
    AccelBuffer.write(ay);
  }
  if (Gyroscope = CoreMPU.measureGyro(); Gyroscope) {
    Gyroscope->get(gx, gy, gz);
    Serial.print("Gyroscope:           ");
    Serial.print(gx);
    GyroBuffer.write(gx);
    Serial.print("       ");
    Serial.print(gy);
    GyroBuffer.write(gy);
    Serial.print("       ");
    Serial.println(gz);
    GyroBUffer.write(gz);
  }
}
}