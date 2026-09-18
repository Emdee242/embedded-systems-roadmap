#include <Wire.h>
class MPU6050{
private:
const uint8_t POWER_MANAGEMENT_REGISTER = 0x6B;
const uint8_t MPU_ADDRESS = 0x68;
uint8_t SLEEP_MASK = 1 << 6;
uint8_t CYCLE_MASK = 1 << 5;
int powerManagementRegisterValue;
public:
void sleepAddress(bool x){
  if(x){
Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(POWER_MANAGEMENT_REGISTER);
  Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDRESS, 1);
    powerManagementRegisterValue = Wire.read() | SLEEP_MASK;
    Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(POWER_MANAGEMENT_REGISTER);
  Wire.write(powerManagementRegisterValue);
  Wire.endTransmission(true); 
  }else{
Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(POWER_MANAGEMENT_REGISTER);
  Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDRESS, 1);
    powerManagementRegisterValue = Wire.read() & ~SLEEP_MASK;
    Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(POWER_MANAGEMENT_REGISTER);
  Wire.write(powerManagementRegisterValue);
  Wire.endTransmission(true); 
  }
}
void cycleAddress(bool x){
    if(x){
Wire.beginTransmission(MPU_ADDRESS);
Wire.write(POWER_MANAGEMENT_REGISTER);
Wire.endTransmission(false);
Wire.requestFrom(MPU_ADDRESS, 1);
powerManagementRegisterValue = Wire.read() | CYCLE_MASK;
Wire.beginTransmission(MPU_ADDRESS, 1);
Wire.write(POWER_MANAGEMENT_REGISTER);
Wire.write(powerManagementRegisterValue);
Wire.endTransmission(true);
}else{
Wire.beginTransmission(MPU_ADDRESS);
Wire.write(POWER_MANAGEMENT_REGISTER);
Wire.endTransmission(false);
Wire.requestFrom(MPU_ADDRESS, 1);
powerManagementRegisterValue = Wire.read() & ~CYCLE_MASK;
Wire.beginTransmission(MPU_ADDRESS, 1);
Wire.write(POWER_MANAGEMENT_REGISTER);
Wire.write(powerManagementRegisterValue);
Wire.endTransmission(true);
    }
  }
};
void setup(){
Wire.begin();
Setup.begin(9600);
}
void loop(){

}