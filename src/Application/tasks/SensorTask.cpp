#include "SensorTask.h"
#include "../../drivers/Mpu6500.h"
#include "../../core/CircularBuffer.h"
#include "../../core/Debouncer.h"
#include <Arduino.h>
#include <optional>
void sensorTaskEntry(void *parameters){
    SensorTaskParam *SensorParameter = static_cast<SensorTaskParam*>(parameters);
    QueueTask SensorTaskEntry;
for(;;){
    SensorParameter->debounce->update();
        switch (SensorParameter->state) {
        case (CurrentState::ACTIVE):
        SensorTaskEntry.QueueMessage = CurrentState::ACTIVE;
            if (SensorParameter->debounce->lift()) {
                SensorParameter -> state = CurrentState::IDLE;
            }
            if (*SensorParameter->Accelerometer = SensorParameter->mpu->measureAccel(); *SensorParameter->Accelerometer) {
                float ax;
                float ay;
                float az;
                (*SensorParameter->Accelerometer)->get(SensorTaskEntry.QueueVariables.ax, SensorTaskEntry.QueueVariables.ay, SensorTaskEntry.QueueVariables.az);
                SensorParameter->AccelBuffer->write(SensorTaskEntry.QueueVariables.ax);
                SensorParameter->AccelBuffer->write(SensorTaskEntry.QueueVariables.ay);
                SensorParameter->AccelBuffer->write(SensorTaskEntry.QueueVariables.az);
            }
            if (*SensorParameter->Gyroscope = SensorParameter->mpu->measureGyro(); *SensorParameter->Gyroscope) {
                float gx;
                float gy;
                float gz;
                (*SensorParameter->Gyroscope)->get(SensorTaskEntry.QueueVariables.gx, SensorTaskEntry.QueueVariables.gy, SensorTaskEntry.QueueVariables.gz);
                SensorParameter->GyroBuffer->write(SensorTaskEntry.QueueVariables.gx);
                SensorParameter->GyroBuffer->write(SensorTaskEntry.QueueVariables.gy);
                SensorParameter->GyroBuffer->write(SensorTaskEntry.QueueVariables.gz);

            }
            break;
        case (CurrentState::IDLE):
        SensorTaskEntry.QueueMessage = CurrentState::IDLE;
            if (SensorParameter->debounce->fall()) {
                SensorParameter -> state = CurrentState::ACTIVE;
            }
            break;
        default:
        SensorParameter->logger->Log("Invalid State", Severity::ERROR);
            break;
        }
        if(xQueueSendToBack(*SensorParameter->sensorHandle, &SensorTaskEntry, pdMS_TO_TICKS( 30 )) != pdPASS){
            SensorParameter->logger->Log("Timeout (Queue is full, overwriting)", Severity::WARN);
            xQueueOverwrite(SensorParameter->sensorHandle, &SensorTaskEntry);
        };
        vTaskDelay(pdMS_TO_TICKS( 1000 ));
}
}
