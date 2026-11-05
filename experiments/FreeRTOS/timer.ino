#include "../../src/drivers/Button.h"
#include "../../src/core/Debouncer.h"
SemaphoreHandle_t buttonSemaphore = xSemaphoreCreateBinary();
int buttonPin = 7;
Button TestButton(buttonPin);
void printButton(void *param){

}
void buttonInterrupt(int x){
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
xSemaphoreGiveFromISR(buttonSemaphore, &xHigherPriorityTaskWoken);
portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
void setup(){
    TestButton.begin();
    xTaskCreate(senseButton, "Sense Button", 1000, NULL, 1, NULL);
    xTaskCreate(printButton, "Print Button", 1000, NULL, 2, NULL);
    attachInterrupt(buttonPin, buttonInterrupt, FALLING);
}