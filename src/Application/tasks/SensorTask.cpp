#include "SensorTask.h"
#include "../../drivers/Mpu6500.h"
#include "../../core/CircularBuffer.h"
#include "../../core/Debouncer.h"
#include <Arduino.h>
#include <optional>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>
void sensorTaskEntry(void *parameters){
    SensorTaskParam *SensorParameter = static_cast<SensorTaskParam*>(parameters);
    QueueTask SensorQueueTaskEntry;
for(;;){
    SensorParameter->debounce->update();
        switch (SensorParameter->state) {
        case (CurrentState::ACTIVE):
        SensorQueueTaskEntry.QueueMessage = CurrentState::ACTIVE;
            if (SensorParameter->debounce->lift()) {
                SensorParameter -> state = CurrentState::IDLE;
            }
            if (*SensorParameter->Accelerometer = SensorParameter->mpu->measureAccel(); *SensorParameter->Accelerometer) {
                float ax;
                float ay;
                float az;
                (*SensorParameter->Accelerometer)->get(SensorQueueTaskEntry.QueueVariables.ax, SensorQueueTaskEntry.QueueVariables.ay, SensorQueueTaskEntry.QueueVariables.az);
                SensorParameter->AccelBuffer->write(SensorQueueTaskEntry.QueueVariables.ax);
                SensorParameter->AccelBuffer->write(SensorQueueTaskEntry.QueueVariables.ay);
                SensorParameter->AccelBuffer->write(SensorQueueTaskEntry.QueueVariables.az);
            }
            if (*SensorParameter->Gyroscope = SensorParameter->mpu->measureGyro(); *SensorParameter->Gyroscope) {
                float gx;
                float gy;
                float gz;
                (*SensorParameter->Gyroscope)->get(SensorQueueTaskEntry.QueueVariables.gx, SensorQueueTaskEntry.QueueVariables.gy, SensorQueueTaskEntry.QueueVariables.gz);
                SensorParameter->GyroBuffer->write(SensorQueueTaskEntry.QueueVariables.gx);
                SensorParameter->GyroBuffer->write(SensorQueueTaskEntry.QueueVariables.gy);
                SensorParameter->GyroBuffer->write(SensorQueueTaskEntry.QueueVariables.gz);

            }
            break;
        case (CurrentState::IDLE):
        SensorQueueTaskEntry.QueueMessage = CurrentState::IDLE;
            if (SensorParameter->debounce->fall()) {
                SensorParameter -> state = CurrentState::ACTIVE;
            }
            break;
        default:
        SensorParameter->logger->Log("Invalid State", Severity::ERROR);
            break;
        }
        if(xQueueSendToBack(*SensorParameter->sensorHandle, &SensorQueueTaskEntry, pdMS_TO_TICKS( 30 )) != pdPASS){
            xQueueOverwrite(*SensorParameter->sensorHandle, &SensorQueueTaskEntry);
        };
}
}
