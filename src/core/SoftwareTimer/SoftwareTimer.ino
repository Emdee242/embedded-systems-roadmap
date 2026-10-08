#include "SoftwareTimer.h"
const unsigned long specificTimer = 1000;
SoftwareTimer sensorTimer;
void setup(){
Serial.begin(9600);
sensorTimer.setTimer(specificTimer);
sensorTimer.reset();
}
void loop(){
if(sensorTimer.intervalPassed()){
  Serial.println(1);
}
}