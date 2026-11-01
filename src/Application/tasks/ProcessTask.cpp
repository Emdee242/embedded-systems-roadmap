#include "ProcessTask.h"
#include "SensorTask.h"
#include "../Application.h"
#include "../../drivers/Mpu6500.h"
static void processTaskEntry(void *parameters){
    QueueHandle_t *processHandle = static_cast<*QueueHandle_t>(parameters);
    QueueTask ProcessedMessage;
for(;;){
    if(xQueueRecieve(*processHandle->messageHandle, &ProcessedMessage, pdMS_TO_TICKS(30)) == pdPASS){
        if(ProcessedMessage.QueueMessage == MessageType::BUTTON_HELD){
                Serial.print("Accelerometer:       ");
                Serial.print(ProcessedMessage.QueueVariables.ax);
                Serial.print("       ");
                Serial.print(ProcessedMessage.QueueVariables.ay);
                Serial.print("       ");
                Serial.println(ProcessedMessage.QueueVariables.az);
                Serial.print("Gyroscope:       ");
                Serial.print(ProcessedMessage.QueueVariables.gx);
                Serial.print("       ");
                Serial.print(ProcessedMessage.QueueVariables.gy);
                Serial.print("       ");
                Serial.println(ProcessedMessage.QueueVariables.gz);
            }else{
            Serial.println("----------------------");
            }
        }
    }
}
