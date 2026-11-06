#include "../../src/drivers/Button.h"
#include "../../src/core/Debouncer.h"
SemaphoreHandle_t buttonSemaphore = xSemaphoreCreateBinary();
TimerHandle_t buttonTimer;
int buttonPin = 7;
Button TestButton(buttonPin);
void printButton(void *param){
    for(;;){
if(xSemaphoreTake(buttonSemaphore, portMAX_DELAY) == pdTRUE){
    xTimerStart(buttonTimer, pdMS_TO_TICKS(30));
            Serial.println("Thy button is pressed!!!");
        }

    }
}
void buttonInterrupt(){
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
xSemaphoreGiveFromISR(buttonSemaphore, &xHigherPriorityTaskWoken);
portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
void buttonCallback(){
xSemaphoreGive(buttonTimer);
}
void setup(){
    TestButton.begin();
    xTaskCreate(printButton, "Print Button", 1000, NULL, 1, NULL);
    attachInterrupt(buttonPin, buttonInterrupt, FALLING);
    buttonTimer = xTimerCreate("buttonTimer", pdMS_TO_TICKS(1000), pdTRUE, NULL, buttonCallback);
}
void loop(){}