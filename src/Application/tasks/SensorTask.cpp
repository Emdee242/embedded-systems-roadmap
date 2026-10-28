#include "SensorTask.h"
#include "../../drivers/Mpu6500.h"
#include <Arduino.h>
#include <Wire.h>
 void SensorTask::task1(void *parameters){
    for(;;){
        if (Accelerometer = CoreMPU.measureAccel(); Accelerometer) {
                float ax;
                float ay;
                float az;
                Accelerometer->get(ax, ay, az);
                Serial.print("Accelerometer:       ");
                Serial.print(ax);
                Serial.print("       ");
                Serial.print(ay);
                Serial.print("       ");
                Serial.println(az);
            }
            if (Gyroscope = CoreMPU.measureGyro(); Gyroscope) {
                float gx;
                float gy;
                float gz;
                Gyroscope->get(gx, gy, gz);
                Serial.print("Gyroscope:           ");
                Serial.print(gx);
                Serial.print("       ");
                Serial.print(gy);
                Serial.print("       ");
                Serial.println(gz);
            }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
void SensorTask::start(){
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
    NULL,
    1,
    NULL
);   
}
