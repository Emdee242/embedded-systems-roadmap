#include "SensorTask.h"
#include "../../drivers/Mpu6500.h"
#include "../../core/CircularBuffer.h"
#include "../../core/Debouncer.h"
#include "../Application.h"
#include <Arduino.h>
#include <optional>
void sensorTaskEntry(void *parameters){
    SensorTaskParam *SensorParameter = static_cast<SensorTaskParam*>(parameters);
    SensorVariables SensorTaskVariables;
    MessageType sensorMessage;
for(;;){
    SensorParameter->debounce->update();
        switch (*SensorParameter->state) {
        case (CurrentState::ACTIVE):
        SensorParameter->sensorMessage = MessageType::BUTTON_HELD;
            if (SensorParameter->debounce->lift()) {
                *SensorParameter -> state = CurrentState::IDLE;
            }
            if (*SensorParameter->Accelerometer = SensorParameter->mpu->measureAccel(); *SensorParameter->Accelerometer) {
                float ax;
                float ay;
                float az;
                *SensorParameter->Accelerometer->get(SensorTaskVariables.ax, SensorTaskVariables.ay, SensorTaskVariables.az);
                SensorParameter->AccelBuffer->write(SensorTaskVariables.ax);
                SensorParameter->AccelBuffer->write(SensorTaskVariables.ay);
                SensorParameter->AccelBuffer->write(SensorTaskVariables.az);
            }
            if (*SensorParameter->Gyroscope = SensorParameter->mpu->measureGyro(); *SensorParameter->Gyroscope) {
                float gx;
                float gy;
                float gz;
                *SensorParameter->Gyroscope->get(SensorTaskVariables.gx, SensorTaskVariables.gy, SensorTaskVariables.gz);
                SensorParameter->GyroBuffer->write(SensorTaskVariables.gx);
                SensorParameter->GyroBuffer->write(SensorTaskVariables.gy);
                SensorParameter->GyroBuffer->write(SensorTaskVariables.gz);

            }
            break;
        case (CurrentState::IDLE):
        SensorParameter->sensorMessage = MessageType::BUTTON_RELEASED;
            if (SensorParameter->debounce->fall()) {
                *SensorParameter -> state = CurrentState::ACTIVE;
            }
            break;
        default:
            break;
        }
        xQueueSendToBack(SensorParamter->messageHandle, *SensorMessage, pdMS_TO_TICKS(30));
        xQueueSendToBack(SensorParameter->sensorHandle, &SensorTaskVariables, pdMS_TO_TICKS( 30 ));
        vTaskDelay(pdMS_TO_TICKS( 1000 ));
}
}
