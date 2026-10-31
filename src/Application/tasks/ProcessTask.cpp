#include "ProcessTask.h"
#include "SensorTask.h"
#include "../Application.h"
#include "../../drivers/Mpu6500.h"
static void processTaskEntry(void *parameters){
    QueueHandles *processHandle = static_cast<*QueueHandles>(parameters);
    SensorVariables SensorTaskVariables;
    MessageType ProcessedMessage;
for(;;){
    if(xQueueRecieve(*processHandle->messageHandle, &ProcessedMessage, pdMS_TO_TICKS(30))){
        if(ProcessedMessage == MessageType::BUTTON_HELD){
            if(xQueueRecieve(&processHandle->sensorHandle, &SensorTaskVariables, pdMS_TO_TICKS(30)) == pdPASS){
                Serial.print("Accelerometer:       ");
                Serial.print(SensorTaskVariables.ax);
                Serial.print("       ");
                Serial.print(SensorTaskVariables.ay);
                Serial.print("       ");
                Serial.println(SensorTaskVariables.az);
                Serial.print("Gyroscope:       ");
                Serial.print(SensorTaskVariables.gx);
                Serial.print("       ");
                Serial.print(SensorTaskVariables.gy);
                Serial.print("       ");
                Serial.println(SensorTaskVariables.gz);
                }
            }else{
            Serial.println("----------------------");
            }
        }
    }
}
