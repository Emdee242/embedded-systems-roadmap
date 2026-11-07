#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
SemaphoreHandle_t buttonSemaphore = NULL;
TimerHandle_t buttonTimer = NULL;
int buttonPin = 7;
void printButton(void *param){
    for(;;){
if(xSemaphoreTake(buttonSemaphore, portMAX_DELAY) == pdTRUE){
    xTimerStart(buttonTimer, pdMS_TO_TICKS(0));
            Serial.println("Thy button is pressed!!!");
        }

    }
}
void buttonInterrupt(){
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
xSemaphoreGiveFromISR(buttonSemaphore, &xHigherPriorityTaskWoken);
portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
void buttonCallback(TimerHandle_t timer){
xSemaphoreGive(buttonSemaphore);
}
void setup(){
    pinMode(buttonPin, INPUT_PULLUP);;
    buttonSemaphore = xSemaphoreCreateBinary();
    xTaskCreate(printButton, "Print Button", 1000, NULL, 1, NULL);
    buttonTimer = xTimerCreate("buttonTimer", pdMS_TO_TICKS(1000), pdTRUE, NULL, buttonCallback);    
    attachInterrupt(buttonPin, buttonInterrupt, FALLING);
}
void loop(){}