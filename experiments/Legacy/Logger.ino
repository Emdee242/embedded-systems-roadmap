#include "Logger.h"
#include <Arduino.h>
Logger testLog;
void setup(){
pinMode(7, INPUT);
testLog.setLimit(Severity::INFO);
}
void loop(){
if(digitalRead(7) == HIGH){
testLog.Log("Sensor noise detected", Severity::WARN);   // This whole if statement is just for demonstration.. holding the button doesn't translate to sensor noise
}
}