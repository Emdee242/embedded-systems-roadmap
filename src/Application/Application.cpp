#include "Application.h"
#include "../core/CircularBuffer.h"
#include "../core/Debouncer.h"
#include "../core/SoftwareTimer.h"
#include "../drivers/Button.h"
#include "../drivers/Mpu6500.h"
#include "tasks/ProcessTask.h"
#include "tasks/SensorTask.h"
#include <Wire.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>
void Application::start() {
    Wire.begin();
    Serial.begin(115200);
    CoreButton.begin();
    CoreTimer.reset();
    CoreTimer.setTimer(readInterval);
    CoreMPU.begin();
    CoreMPU.sleep(0);
    CoreMPU.cycle(0);
    CoreMPU.configAccel(0, 0);
    CoreMPU.configGyro(0, 0);
    CoreMPU.firstLog.setLimit(Severity::INFO);
    CoreTaskParam.button = &CoreButton;
    CoreTaskParam.debounce = &CoreDebouncer;
    CoreTaskParam.timer = &CoreTimer;
    CoreTaskParam.AccelBuffer = &AccelBuffer;
    CoreTaskParam.GyroBuffer = &GyroBuffer;
    CoreTaskParam.mpu = &CoreMPU;
    CoreTaskParam.logger = &CoreLogger;
    CoreTaskParam.Accelerometer = &Accelerometer;
    CoreTaskParam.Gyroscope = &Gyroscope;
    CorePTaskParam.logger = &CoreLogger;
    startQueue = xQueueCreate(1, sizeof(QueueTask));
    if(startQueue == nullptr){
        Serial.println("Queue creation failed!");
        return;
    }
    CoreTaskParam.sensorHandle = &startQueue;
    CorePTaskParam.processHandle = &startQueue;
    xTaskCreate(sensorTaskEntry, "sensor task", 4096, &CoreTaskParam, 2, nullptr);
    xTaskCreate(processTaskEntry, "process task", 4096, &CorePTaskParam, 1, nullptr);
}