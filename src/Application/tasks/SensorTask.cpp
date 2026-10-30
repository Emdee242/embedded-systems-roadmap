#include "SensorTask.h"
#include "../../drivers/Mpu6500.h"
#include "../../core/CircularBuffer.h"
#include "../../core/Debouncer.h"
#include "../../core/SoftwareTimer.h"
#include "../../drivers/Button.h"
#include "../Application.h"
#include <Arduino.h>
#include <Arduino.h>
#include <Wire.h>
#include <optional>
void sensorTaskEntry(void *parameters){
for(;;){
    SensorTaskParam *SensorParameter = static_cast<SensorTaskParam*>(parameters);
    SensorParameter->debounce->update();
    if (SensorParameter->timer->intervalPassed()) {
        switch (*SensorParameter->state) {
        case (CurrentState::ACTIVE):
            if (SensorParameter->debounce->lift()) {
                *SensorParameter -> state = CurrentState::IDLE;
            }
            if (*SensorParameter->Accelerometer = SensorParameter->mpu->measureAccel(); *SensorParameter->Accelerometer) {
                float ax;
                float ay;
                float az;
                *SensorParameter->Accelerometer->get(ax, ay, az);
                SensorParameter->AccelBuffer->write(ax);
                SensorParameter->AccelBuffer->write(ay);
                SensorParameter->AccelBuffer->write(az);
            }
            if (*SensorParameter->Gyroscope = SensorParameter->mpu->measureGyro(); *SensorParameter->Gyroscope) {
                float gx;
                float gy;
                float gz;
                *SensorParameter->Gyroscope->get(gx, gy, gz);
                SensorParameter->GyroBuffer->write(gx);
                SensorParameter->GyroBuffer->write(gy);;
                SensorParameter->GyroBuffer->write(gz);;
            }
            break;
        case (CurrentState::IDLE):
            if (SensorParameter->debounce->fall()) {
                *SensorParameter -> state = CurrentState::ACTIVE;
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
