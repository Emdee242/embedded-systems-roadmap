#include "Led.h"
unsigned long checkSystemTime;
unsigned long checkRefTime = 0;
int ledState = 1;
Led led1(7);  
void setup() {
  // put your setup code here, to run once:
led1.begin();

}

void loop() { 
  // put your main code here, to run repeatedly:
checkSystemTime = millis();
if((checkSystemTime - checkRefTime)  >= 500){
  checkRefTime = checkSystemTime;
  if(ledState){
    led1.on();
    ledState = 0;
  }else{
    led1.off();
    ledState = 1;
  }
}
}
