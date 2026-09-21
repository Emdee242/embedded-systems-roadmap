#include <Wire.h>
#include <optional>
struct AccelerometerReading{
  public:
  uint16_t x;
  uint16_t y;
  uint16_t z;
  friend class MPU6050;
};
struct GyroscopeReading{
  public:
  uint16_t x;
  uint16_t y;
  uint16_t z;
  friend class MPU6050;
};
class MPU6050{
private:
const uint8_t POWER_MANAGEMENT_REGISTER = 0x6B;
const uint8_t MPU_ADDRESS = 0x68;
const uint8_t SIGNAL_PATH_RESET_ADDRESS = 0x68;
const uint8_t USER_CONTROL_ADDRESS = 0x6A;
const uint8_t WHO_AM_I_REGISTER = 0x75;
const uint8_t GYRO_ADDRESS = 0x67;
const uint8_t ACCEL_ADDRESS = 0x59;
const uint8_t WHO_AM_I_VALUE = 0x68;
uint8_t SLEEP_MASK = 1 << 6;
uint8_t CYCLE_MASK = 1 << 5;
uint8_t GENERAL_RESET_MASK = 1 << 0;
uint8_t GYRO_RESET_MASK = 1 << 2;
uint8_t ACCEL_RESET_MASK = 1 << 1;
bool isReady = false;
int powerManagementRegisterValue;
int signalPathResetValue;
int userControlValue;
public:
void begin(){
Wire.beginTransmission(MPU_ADDRESS);
Wire.write(WHO_AM_I_REGISTER);
Wire.endTransmission(false);
Wire.requestFrom(MPU_ADDRESS, 1);
if(Wire.read() == WHO_AM_I_VALUE){
  isReady = true;
}else{
  isReady = false;
}
}
void sleep(bool x){
  if(isReady){
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
  }else{
    return;
  }
}
void cycle(bool x){
  if(isReady){
    if(x){
Wire.beginTransmission(MPU_ADDRESS);
Wire.write(POWER_MANAGEMENT_REGISTER);
Wire.endTransmission(false);
Wire.requestFrom(MPU_ADDRESS, 1);
powerManagementRegisterValue = Wire.read() | CYCLE_MASK;
Wire.beginTransmission(MPU_ADDRESS);
Wire.write(POWER_MANAGEMENT_REGISTER);
Wire.write(powerManagementRegisterValue);
Wire.endTransmission(true);
}else{
Wire.beginTransmission(MPU_ADDRESS);
Wire.write(POWER_MANAGEMENT_REGISTER);
Wire.endTransmission(false);
Wire.requestFrom(MPU_ADDRESS, 1);
powerManagementRegisterValue = Wire.read() & ~CYCLE_MASK;
Wire.beginTransmission(MPU_ADDRESS);
Wire.write(POWER_MANAGEMENT_REGISTER);
Wire.write(powerManagementRegisterValue);
Wire.endTransmission(true);
    }
  }else{
    return;
    }
  }
void generalReset(bool x){
if(isReady){
  if(x){
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(USER_CONTROL_ADDRESS);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDRESS, 1);
    userControlValue = Wire.read() | GENERAL_RESET_MASK;
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(USER_CONTROL_ADDRESS);
    Wire.write(userControlValue);
    Wire.endTransmission(true);
  }else{
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(USER_CONTROL_ADDRESS);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDRESS, 1);
    userControlValue = Wire.read() & ~GENERAL_RESET_MASK;
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(USER_CONTROL_ADDRESS);
    Wire.write(userControlValue);
    Wire.endTransmission(true);
    }
    }else{
  return;
  }
}
void accelReset(bool x){
    if(isReady){
  if(x){
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(SIGNAL_PATH_RESET_ADDRESS);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDRESS, 1);
    signalPathResetValue = Wire.read() | GYRO_RESET_MASK;
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(SIGNAL_PATH_RESET_ADDRESS);
    Wire.write(signalPathResetValue);
    Wire.endTransmission(true);
  }else{
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(SIGNAL_PATH_RESET_ADDRESS);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDRESS, 1);
    signalPathResetValue = Wire.read() & ~GYRO_RESET_MASK;
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(SIGNAL_PATH_RESET_ADDRESS);
    Wire.write(signalPathResetValue);
    Wire.endTransmission(true);
      }
    }else{
      return;
    }
}
void gyroReset(bool x){
  if(isReady){
  if(x){
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(SIGNAL_PATH_RESET_ADDRESS);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDRESS, 1);
    signalPathResetValue = Wire.read() | ACCEL_RESET_MASK;
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(SIGNAL_PATH_RESET_ADDRESS);
    Wire.write(signalPathResetValue);
    Wire.endTransmission(true);
  }else{
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(SIGNAL_PATH_RESET_ADDRESS);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDRESS, 1);
    signalPathResetValue = Wire.read() & ~ACCEL_RESET_MASK;
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(SIGNAL_PATH_RESET_ADDRESS);
    Wire.write(signalPathResetValue);
    Wire.endTransmission(true);
    }
  }else{
    return;
  }
}
std::optional<AccelerometerReading>measureAccel(){
    if(isReady){
      AccelerometerReading Accelerometer;
      uint8_t accel_X_H;
      uint8_t accel_X_L;
      uint8_t accel_Y_H;
      uint8_t accel_Y_L;
      uint8_t accel_Z_H;
      uint8_t accel_Z_L;
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(ACCEL_ADDRESS);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDRESS, 6);
  accel_X_H = Wire.read();
  accel_X_L = Wire.read();
  Accelerometer.x = accel_X_H << 8;
  Accelerometer.x |= accel_X_L;
  accel_Y_H = Wire.read();
  accel_Y_L = Wire.read();
  Accelerometer.y = accel_Y_H << 8;
  Accelerometer.y |= accel_Y_L;
  accel_Z_H = Wire.read();
  accel_Z_L = Wire.read();
  Accelerometer.z = accel_Z_H << 8;
  Accelerometer.z |= accel_Z_L;
  return Accelerometer;
    }else{
      return{};
    }
  }
std::optional<GyroscopeReading>measureGyro(){
    if(isReady){
      GyroscopeReading Gyroscope;
      uint8_t gyro_X_H;
      uint8_t gyro_X_L;
      uint8_t gyro_Y_H;
      uint8_t gyro_Y_L;
      uint8_t gyro_Z_H;
      uint8_t gyro_Z_L;
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(GYRO_ADDRESS);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDRESS, 6);
  gyro_X_H = Wire.read();
  gyro_X_L = Wire.read();
  Gyroscope.x = gyro_X_H << 8;
  Gyroscope.x |= gyro_X_L;
  gyro_Y_H = Wire.read();
  gyro_Y_L = Wire.read();
  Gyroscope.y = gyro_Y_H << 8;
  Gyroscope.y |= gyro_Y_L;
  gyro_Z_H = Wire.read();
  gyro_Z_L = Wire.read();
  Gyroscope.z = gyro_Z_H << 8;
  Gyroscope.z |= gyro_Z_L;
  return Gyroscope;
  }else{
  return {};
    }
  }
};
std::optional<AccelerometerReading> Accelerometer;
std::optional<GyroscopeReading> Gyroscope;
MPU6050 FirstMPU;
void setup(){
Wire.begin();
Serial.begin(9600);
FirstMPU.begin();
FirstMPU.sleep(0);
FirstMPU.cycle(1);
}
void loop(){
  
  if(FirstMPU.measureAccel()){
  Accelerometer = FirstMPU.measureAccel();  
  }
if(FirstMPU.measureAccel()){
Gyroscope = FirstMPU.measureGyro();  
}
}