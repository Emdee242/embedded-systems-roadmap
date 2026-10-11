#include "CircularBuffer.h"
CircularBuffer Buffer1;
void setup(){
Serial.begin(115200);
}
void loop(){
Buffer1.write(42);
int value = Buffer1.read();
Serial.println(value);
}