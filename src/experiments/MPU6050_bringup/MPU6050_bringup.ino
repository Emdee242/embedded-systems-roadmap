#include <Wire.h>
const uint8_t WHO_AM_I_REGISTER = 0x75;
const uint8_t POWER_MANAGEMENT_REGISTER = 0x6B;
const uint8_t mpuAddress = 0x68;
uint8_t bitMask = 1 << 6;
int WHO_AM_I_OUTPUT;
int POWER_MANAGEMENT_REGISTER_OUTPUT;
unsigned long updateSleep = 0;
bool isSleep = false;
void setup(){
Serial.begin(9600);
Wire.begin();
}
void loop(){
if(isSleep == false){
  updateSleep = millis();
  isSleep = true;
}
Wire.beginTransmission(mpuAddress);
Wire.write(WHO_AM_I_REGISTER);
Wire.endTransmission(false);
Wire.requestFrom(mpuAddress, 1);
WHO_AM_I_OUTPUT = Wire.read();
Serial.print(WHO_AM_I_OUTPUT);
if(millis() - updateSleep >= 1000){
  Wire.beginTransmission(mpuAddress);
  Wire.write(POWER_MANAGEMENT_REGISTER);
  Wire.endTransmission(false);
    Wire.requestFrom(mpuAddress, 1);
    POWER_MANAGEMENT_REGISTER_OUTPUT = Wire.read() | bitMask;
    Wire.beginTransmission(mpuAddress);
  Wire.write(POWER_MANAGEMENT_REGISTER);
  Wire.write(POWER_MANAGEMENT_REGISTER_OUTPUT);
  Wire.endTransmission(true);
  Wire.beginTransmission(mpuAddress);
  Wire.write(POWER_MANAGEMENT_REGISTER);
  Wire.endTransmission(false);
  Wire.requestFrom(mpuAddress, 1);
  POWER_MANAGEMENT_REGISTER_OUTPUT = Wire.read();
Serial.println((POWER_MANAGEMENT_REGISTER_OUTPUT >> 6) & 1);
isSleep = false;
}
}