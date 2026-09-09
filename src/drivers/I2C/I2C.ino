#include <Wire.h>
void setup(){
Serial.begin(9600);
Wire.begin();
int mpuRegister = 0x75;
int mpuAddress = 0x68;
int consoleOutput;
Wire.beginTransmission(mpuAddress);
Wire.write(mpuRegister);
Wire.endTransmission(true);
Wire.requestFrom(mpuAddress, 1);
consoleOutput = Wire.read();
Serial.print(consoleOutput, HEX);
}
void loop(){

}