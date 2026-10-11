#include "Button.h"
#include "Debouncer.h"
Button Button1(7);
Debouncer Debouncer1(Button1);
void setup(){
Serial.begin(9600);
Button1.begin();
}
void loop(){
Debouncer1.update();
if(Debouncer1.fall()){
  Serial.println(1);
}
}
