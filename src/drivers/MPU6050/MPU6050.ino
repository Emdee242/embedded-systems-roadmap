#include <Wire.h>
#include <optional>
enum class Severity {
  INFO,
  WARN,
  ERROR

};
class Logger {
private:
  Severity maxLogger = Severity::INFO;
public:
  void setLimit(Severity Level) {
    maxLogger = Level;
  }
  void Log(const char *message, Severity Level) {

    if (Level >= maxLogger) {
      switch (Level) {
        case (Severity::INFO):
          Serial.print(message);
          Serial.print("      ");
          Serial.println("INFO");
          break;
        case (Severity::WARN):
          Serial.print(message);
          Serial.print("      ");
          Serial.println("WARN");
          break;
        case (Severity::ERROR):
          Serial.print(message);
          Serial.print("      ");
          Serial.println("ERROR");
          break;
      }
    } else {
      Serial.print(message);
      Serial.print("      ");
      Serial.println("Value suppressed, out of the range of the threshold");
    }
  }
};

struct AccelerometerReading {
private:
  int16_t x;
  int16_t y;
  int16_t z;
  friend class MPU6050;
public:
  void get(int16_t &x1, int16_t &y2, int16_t &z3) const {
    x1 = x;
    y2 = y;
    z3 = z;
  }
};
struct GyroscopeReading {
private:
  int16_t x;
  int16_t y;
  int16_t z;
  friend class MPU6050;
public:
  void get(int16_t &x1, int16_t &y2, int16_t &z3) {
    x1 = x;
    y2 = y;
    z3 = z;
  }
};
class MPU6050 {
private:
  const uint8_t POWER_MANAGEMENT_REGISTER = 0x6B;
  const uint8_t MPU_ADDRESS = 0x68;
  const uint8_t SIGNAL_PATH_RESET_ADDRESS = 0x68;
  const uint8_t USER_CONTROL_ADDRESS = 0x6A;
  const uint8_t WHO_AM_I_REGISTER = 0x75;
  const uint8_t GYRO_ADDRESS = 0x43;
  const uint8_t ACCEL_ADDRESS = 0x3B;
  const uint8_t WHO_AM_I_VALUE = 0x68;
  uint8_t SLEEP_MASK = 1 << 6;
  uint8_t CYCLE_MASK = 1 << 5;
  uint8_t GENERAL_RESET_MASK = 1 << 0;
  uint8_t GYRO_RESET_MASK = 1 << 2;
  uint8_t ACCEL_RESET_MASK = 1 << 1;
  bool isMpuReady = false;
  bool 
  int powerManagementRegisterValue;
  int signalPathResetValue;
  int userControlValue;
public:
  Logger firstLog;
  bool begin() {
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(WHO_AM_I_REGISTER);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDRESS, 1);
    if (Wire.read() == WHO_AM_I_VALUE) {
      isMpuReady = true;
      return 1;
    } else {
      isMpuReady = false;
      firstLog.Log("MPU initialization failed", Severity::ERROR);
      return 0;
    }
  }
  void sleep(bool x) {
    if (isReady) {
      if (x) {
        Wire.beginTransmission(MPU_ADDRESS);
        Wire.write(POWER_MANAGEMENT_REGISTER);
        Wire.endTransmission(false);
        Wire.requestFrom(MPU_ADDRESS, 1);
        powerManagementRegisterValue = Wire.read() | SLEEP_MASK;
        Wire.beginTransmission(MPU_ADDRESS);
        Wire.write(POWER_MANAGEMENT_REGISTER);
        Wire.write(powerManagementRegisterValue);
        Wire.endTransmission(true);
      } else {
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
    } else {
      firstLog.Log("MPU sleep operation failed", Severity::ERROR);
      return;
    }
  }
  void cycle(bool x) {
    if (isReady) {
      if (x) {
        Wire.beginTransmission(MPU_ADDRESS);
        Wire.write(POWER_MANAGEMENT_REGISTER);
        Wire.endTransmission(false);
        Wire.requestFrom(MPU_ADDRESS, 1);
        powerManagementRegisterValue = Wire.read() | CYCLE_MASK;
        Wire.beginTransmission(MPU_ADDRESS);
        Wire.write(POWER_MANAGEMENT_REGISTER);
        Wire.write(powerManagementRegisterValue);
        Wire.endTransmission(true);
      } else {
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
    } else {
      firstLog.Log("MPU cycle operation failed", Severity::ERROR);
      return;
    }
  }
  void generalReset(bool x) {
    if (isReady) {
      if (x) {
        Wire.beginTransmission(MPU_ADDRESS);
        Wire.write(USER_CONTROL_ADDRESS);
        Wire.endTransmission(false);
        Wire.requestFrom(MPU_ADDRESS, 1);
        userControlValue = Wire.read() | GENERAL_RESET_MASK;
        Wire.beginTransmission(MPU_ADDRESS);
        Wire.write(USER_CONTROL_ADDRESS);
        Wire.write(userControlValue);
        Wire.endTransmission(true);
      } else {
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
    } else {
      firstLog.Log("MPU general reset operation failed", Severity::ERROR);
      return;
    }
  }
  void accelReset(bool x) {
    if (isReady) {
      if (x) {
        Wire.beginTransmission(MPU_ADDRESS);
        Wire.write(SIGNAL_PATH_RESET_ADDRESS);
        Wire.endTransmission(false);
        Wire.requestFrom(MPU_ADDRESS, 1);
        signalPathResetValue = Wire.read() | ACCEL_RESET_MASK;
        Wire.beginTransmission(MPU_ADDRESS);
        Wire.write(SIGNAL_PATH_RESET_ADDRESS);
        Wire.write(signalPathResetValue);
        Wire.endTransmission(true);
      } else {
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
    } else {
      firstLog.Log("MPU accelerometer reset operation failed", Severity::ERROR);
      return;
    }
  }
  void gyroReset(bool x) {
    if (isReady) {
      if (x) {
        Wire.beginTransmission(MPU_ADDRESS);
        Wire.write(SIGNAL_PATH_RESET_ADDRESS);
        Wire.endTransmission(false);
        Wire.requestFrom(MPU_ADDRESS, 1);
        signalPathResetValue = Wire.read() | GYRO_RESET_MASK;
        Wire.beginTransmission(MPU_ADDRESS);
        Wire.write(SIGNAL_PATH_RESET_ADDRESS);
        Wire.write(signalPathResetValue);
        Wire.endTransmission(true);
      } else {
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
    } else {
      firstLog.Log("MPU gyroscope reset operation failed", Severity::ERROR);
      return;
    }
  }
  std::optional<AccelerometerReading> measureAccel() {
    if (isReady) {
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
    } else {
      firstLog.Log("MPU measure acceleration operation failed", Severity::ERROR);
      return {};
    }
  }
  std::optional<GyroscopeReading> measureGyro() {
    if (isReady) {
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
    } else {
      firstLog.Log("MPU measure gyroscope operation failed", Severity::ERROR);
      return {};
    }
  }
};
MPU6050 FirstMPU;
Logger mpuLog;
std::optional<AccelerometerReading> Accelerometer;
std::optional<GyroscopeReading> Gyroscope;
void setup() {
  Wire.begin();
  Serial.begin(9600);
  FirstMPU.begin();
  FirstMPU.sleep(0);
  FirstMPU.cycle(1);
  mpuLog.setLimit(Severity::INFO);
}
void loop() {
  if (Accelerometer = FirstMPU.measureAccel(); Accelerometer) {
    Serial.println("Successful!!");
  }
  if (Gyroscope = FirstMPU.measureGyro(); Gyroscope) {
    Serial.println("Successful!!");
  }
}