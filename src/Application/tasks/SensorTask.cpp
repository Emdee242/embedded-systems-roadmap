#include "SensorTask.h"
#include "../../drivers/Mpu6500.h"
#include "../Application.h"
#include <Arduino.h>
#include <Wire.h>
void SensorTask::sensorTaskEntry(void *parameters){
for(;;){
    Application *SensorApplication = static_cast<Application*>(parameters);
    SensorApplication->CoreDebouncer.update();
    if (ProcessApplication->CoreTimer.intervalPassed()) {
        switch (ProcessApplication->ApplicationState) {
        case (CurrentState::ACTIVE):
            if (CoreDebouncer.lift()) {
                ApplicationState = CurrentState::IDLE;
            }
            if (Accelerometer = CoreMPU.measureAccel(); Accelerometer) {
                float ax;
                float ay;
                float az;
                Accelerometer->get(ax, ay, az);
                AccelBuffer.write(ax);
                AccelBuffer.write(ay);
                AccelBuffer.write(az);
            }
            if (Gyroscope = CoreMPU.measureGyro(); Gyroscope) {
                float gx;
                float gy;
                float gz;
                GyroBuffer.write(gx);
                GyroBuffer.write(gy);
                GyroBuffer.write(gz);
            }
            break;
        case (CurrentState::IDLE):
            if (CoreDebouncer.fall()) {
                ApplicationState = CurrentState::ACTIVE;
            }
            Serial.println("----------------------");
            break;
        default:
            Serial.println(".........................");
            break;
        }
    }
}
}
void SensorTask::start(){
    Wire.begin();
    Serial.begin(115200);
    CoreMPU.begin();
    CoreMPU.sleep(0);
    CoreMPU.cycle(0);
    CoreMPU.configAccel(0, 0);
    CoreMPU.configGyro(0, 0);
    CoreMPU.firstLog.setLimit(Severity::INFO);
xTaskCreate(
    task1,
    "Task 1",
    1000,
    this,
    1,
    NULL
);   
}
