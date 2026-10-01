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
  friend class MPU6500;
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
  friend class MPU6500;
public:
  void get(int16_t &x1, int16_t &y2, int16_t &z3) {
    x1 = x;
    y2 = y;
    z3 = z;
  }
};
class MPU6500 {
private:
  const uint8_t POWER_MANAGEMENT_REGISTER = 0x6B;
  uint8_t MPU_ADDRESS = 0x68;
  const uint8_t SIGNAL_PATH_RESET_ADDRESS = 0x68;
  const uint8_t USER_CONTROL_ADDRESS = 0x6A;
  const uint8_t ACCEL_CONFIG_ADDRESS = 0x1C;
  const uint8_t GYRO_CONFIG_ADDRESS = 0x1B;
  const uint8_t WHO_AM_I_REGISTER = 0x75;
  const uint8_t GYRO_ADDRESS = 0x43;
  const uint8_t ACCEL_ADDRESS = 0x3B;
  const uint8_t WHO_AM_I_VALUE = 0x70;
  uint8_t SLEEP_MASK = 1 << 6;
  uint8_t CYCLE_MASK = 1 << 5;
  uint8_t GENERAL_RESET_MASK = 1 << 0;
  uint8_t GYRO_RESET_MASK = 1 << 2;
  uint8_t ACCEL_RESET_MASK = 1 << 1;
  bool isMpuReady = false;
  bool whoAreYou = false;
  int powerManagementRegisterValue;
  int signalPathResetValue;
  int userControlValue;
  int accelConfigValue;
  int gyroConfigValue;
  TwoWire &MpuWire;
public:
  MPU6500(TwoWire &tw)
    : MpuWire(tw){};
  Logger firstLog;
  int begin() {
    int storeTransmission;
    MpuWire.beginTransmission(MPU_ADDRESS);
    MpuWire.write(WHO_AM_I_REGISTER);
    storeTransmission = MpuWire.endTransmission(false);
    if (storeTransmission == 0) {
      int storeRequest;
      storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 1);
      if (storeRequest == 1) {
        int storeRead;
        storeRead = MpuWire.read();
        if (storeRead == WHO_AM_I_VALUE) {
          isMpuReady = true;
          whoAreYou = true;
          firstLog.Log("Successful", Severity::INFO);
          return 0;
        } else {
          isMpuReady = true;
          whoAreYou = false;
          firstLog.Log("Invalid WHO_AM_I value", Severity::ERROR);
          return 6;
        }
      } else {
        isMpuReady = true;
        whoAreYou = false;
        firstLog.Log("Number of bytes read from begin method does not match the requested amount", Severity::ERROR);
        return 7;
      }
    } else if (storeTransmission == 1) {
      isMpuReady = false;
      whoAreYou = false;
      firstLog.Log("Data is too long", Severity::ERROR);
      return 1;
    } else if (storeTransmission == 2) {
      isMpuReady = false;
      whoAreYou = false;
      firstLog.Log("Invalid device address", Severity::ERROR);
      return 2;
    } else if (storeTransmission == 3) {
      isMpuReady = true;
      whoAreYou = false;
      firstLog.Log("Invalid register address", Severity::ERROR);
      return 3;
    } else if (storeTransmission == 4) {
      isMpuReady = false;
      whoAreYou = false;
      firstLog.Log("Unrecognized error", Severity::ERROR);
      return 4;
    } else if (storeTransmission == 5) {
      isMpuReady = false;
      whoAreYou = false;
      firstLog.Log("Timeout", Severity::ERROR);
      return 5;
    } else {
      isMpuReady = false;
      whoAreYou = false;
      firstLog.Log("non-existing return type, check current endTransmission documentation", Severity::ERROR);
      return 8;
    }
  }
  void setMpuAddress(uint8_t x) {
    MPU_ADDRESS = x;
  }
  void sleep(bool x) {
    if (isMpuReady && whoAreYou) {
      if (x) {
        int storeTransmission;
        MpuWire.beginTransmission(MPU_ADDRESS);
        MpuWire.write(POWER_MANAGEMENT_REGISTER);
        storeTransmission = MpuWire.endTransmission(false);
        if (storeTransmission == 0) {
          int storeRequest;
          storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 1);
          if (storeRequest == 1) {
            powerManagementRegisterValue = MpuWire.read() | SLEEP_MASK;
            MpuWire.beginTransmission(MPU_ADDRESS);
            MpuWire.write(POWER_MANAGEMENT_REGISTER);
            MpuWire.write(powerManagementRegisterValue);
            MpuWire.endTransmission(true);
          } else {
            firstLog.Log("Number of bytes read from the sleep method is not the requested amount", Severity::ERROR);
          }
        } else {
          firstLog.Log("sleep write (1) operation failed", Severity::ERROR);
        }

      } else {
        int storeTransmission;
        MpuWire.beginTransmission(MPU_ADDRESS);
        MpuWire.write(POWER_MANAGEMENT_REGISTER);
        storeTransmission = MpuWire.endTransmission(false);
        if (storeTransmission == 0) {
          int storeRequest;
          storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 1);
          if (storeRequest == 1) {
            powerManagementRegisterValue = MpuWire.read() & ~SLEEP_MASK;
            MpuWire.beginTransmission(MPU_ADDRESS);
            MpuWire.write(POWER_MANAGEMENT_REGISTER);
            MpuWire.write(powerManagementRegisterValue);
            MpuWire.endTransmission(true);
          } else {
            firstLog.Log("Number of bytes read from the sleep method is not the requested amount", Severity::ERROR);
          }

        } else {
          firstLog.Log("sleep write (0) operation failed", Severity::ERROR);
        }
      }
    } else {
      firstLog.Log("MPU sleep operation failed (check begin function)", Severity::ERROR);
      return;
    }
  }
  void cycle(bool x) {
    if (isMpuReady && whoAreYou) {
      if (x) {
        int storeTransmission;
        MpuWire.beginTransmission(MPU_ADDRESS);
        MpuWire.write(POWER_MANAGEMENT_REGISTER);
        storeTransmission = MpuWire.endTransmission(false);
        if (storeTransmission == 0) {
          int storeRequest;
          storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 1);
          if (storeRequest == 1) {
            powerManagementRegisterValue = MpuWire.read() | CYCLE_MASK;
            MpuWire.beginTransmission(MPU_ADDRESS);
            MpuWire.write(POWER_MANAGEMENT_REGISTER);
            MpuWire.write(powerManagementRegisterValue);
            MpuWire.endTransmission(true);
          } else {
            firstLog.Log("Number of bytes read from the cycle method is not the requested amount", Severity::ERROR);
          }

        } else {
          firstLog.Log("MPU cycle write (1) operation failed", Severity::ERROR);
        }

      } else {
        int storeTransmission;
        MpuWire.beginTransmission(MPU_ADDRESS);
        MpuWire.write(POWER_MANAGEMENT_REGISTER);
        storeTransmission = MpuWire.endTransmission(false);
        if (storeTransmission == 0) {
          int storeRequest;
          storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 1);
          if (storeRequest == 1) {
            powerManagementRegisterValue = MpuWire.read() & ~CYCLE_MASK;
            MpuWire.beginTransmission(MPU_ADDRESS);
            MpuWire.write(POWER_MANAGEMENT_REGISTER);
            MpuWire.write(powerManagementRegisterValue);
            MpuWire.endTransmission(true);
          } else {
            firstLog.Log("Number of bytes read from the cycle method is not the requested amount", Severity::ERROR);
          }

        } else {
          firstLog.Log("MPU cycle write (0) operation failed", Severity::ERROR);
        }
      }
    } else {
      firstLog.Log("MPU cycle operation failed (check begin function)", Severity::ERROR);
      return;
    }
  }
  void generalReset(bool x) {
    if (isMpuReady && whoAreYou) {
      if (x) {
        int storeTransmission;
        MpuWire.beginTransmission(MPU_ADDRESS);
        MpuWire.write(USER_CONTROL_ADDRESS);
        storeTransmission = MpuWire.endTransmission(false);
        if (storeTransmission == 0) {
          int storeRequest;
          storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 1);
          if (storeRequest == 1) {
            userControlValue = MpuWire.read() | GENERAL_RESET_MASK;
            MpuWire.beginTransmission(MPU_ADDRESS);
            MpuWire.write(USER_CONTROL_ADDRESS);
            MpuWire.write(userControlValue);
            MpuWire.endTransmission(true);
          } else {
            firstLog.Log("Number of bytes read from the generalReset method is not the requested amount", Severity::ERROR);
          }

        } else {
          firstLog.Log("general reset write (1) operation failed", Severity::ERROR);
        }

      } else {
        int storeTransmission;
        MpuWire.beginTransmission(MPU_ADDRESS);
        MpuWire.write(USER_CONTROL_ADDRESS);
        storeTransmission = MpuWire.endTransmission(false);
        if (storeTransmission == 0) {
          int storeRequest;
          storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 1);
          if (storeRequest == 1) {
            userControlValue = MpuWire.read() & ~GENERAL_RESET_MASK;
            MpuWire.beginTransmission(MPU_ADDRESS);
            MpuWire.write(USER_CONTROL_ADDRESS);
            MpuWire.write(userControlValue);
            MpuWire.endTransmission(true);
          } else {
            firstLog.Log("Number of bytes read from the generalReset method is not the requested amount", Severity::ERROR);
          }

        } else {
          firstLog.Log("general reset write (0) operation failed", Severity::ERROR);
        }
      }
    } else {
      firstLog.Log("MPU general reset operation failed (check begin function)", Severity::ERROR);
      return;
    }
  }

  void accelReset(bool x) {
    if (isMpuReady && whoAreYou) {
      if (x) {
        int storeTransmission;
        MpuWire.beginTransmission(MPU_ADDRESS);
        MpuWire.write(SIGNAL_PATH_RESET_ADDRESS);
        storeTransmission = MpuWire.endTransmission(false);
        if (storeTransmission == 0) {
          int storeRequest;
          storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 1);
          if (storeRequest == 1) {
            signalPathResetValue = MpuWire.read() | ACCEL_RESET_MASK;
            MpuWire.beginTransmission(MPU_ADDRESS);
            MpuWire.write(SIGNAL_PATH_RESET_ADDRESS);
            MpuWire.write(signalPathResetValue);
            MpuWire.endTransmission(true);
          } else {
            firstLog.Log("Number of bytes read from the accelReset method is not the requested amount", Severity::ERROR);
          }
        } else {
          firstLog.Log("accelerometer reset write (1) operation failed", Severity::ERROR);
        }
      } else {
        int storeTransmission;
        MpuWire.beginTransmission(MPU_ADDRESS);
        MpuWire.write(SIGNAL_PATH_RESET_ADDRESS);
        storeTransmission = MpuWire.endTransmission(false);
        if (storeTransmission == 0) {
          int storeRequest;
          storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 1);
          if (storeRequest == 1) {
            signalPathResetValue = MpuWire.read() & ~ACCEL_RESET_MASK;
            MpuWire.beginTransmission(MPU_ADDRESS);
            MpuWire.write(SIGNAL_PATH_RESET_ADDRESS);
            MpuWire.write(signalPathResetValue);
            MpuWire.endTransmission(true);
          } else {
            firstLog.Log("Number of bytes read from the accelReset method is not the requested amount", Severity::ERROR);
          }
        } else {
          firstLog.Log("accelerometer reset write (0) operation failed", Severity::ERROR);
        }
      }
    } else {
      firstLog.Log("MPU accelerometer reset operation failed (check begin function)", Severity::ERROR);
      return;
    }
  }

  void gyroReset(bool x) {
    if (isMpuReady && whoAreYou) {
      if (x) {
        int storeTransmission;
        MpuWire.beginTransmission(MPU_ADDRESS);
        MpuWire.write(SIGNAL_PATH_RESET_ADDRESS);
        storeTransmission = MpuWire.endTransmission(false);
        if (storeTransmission == 0) {
          int storeRequest;
          storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 1);
          if (storeRequest == 1) {
            signalPathResetValue = MpuWire.read() | GYRO_RESET_MASK;
            MpuWire.beginTransmission(MPU_ADDRESS);
            MpuWire.write(SIGNAL_PATH_RESET_ADDRESS);
            MpuWire.write(signalPathResetValue);
            MpuWire.endTransmission(true);
          } else {
            firstLog.Log("Number of bytes read from the gyroReset method is not the requested amount", Severity::ERROR);
          }

        } else {
          firstLog.Log("gyrometer reset write (1) operation failed", Severity::ERROR);
        }
      } else {
        int storeTransmission;
        MpuWire.beginTransmission(MPU_ADDRESS);
        MpuWire.write(SIGNAL_PATH_RESET_ADDRESS);
        storeTransmission = MpuWire.endTransmission(false);
        if (storeTransmission == 0) {
          int storeRequest;
          storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 1);
          if (storeRequest == 1) {
            signalPathResetValue = MpuWire.read() & ~GYRO_RESET_MASK;
            MpuWire.beginTransmission(MPU_ADDRESS);
            MpuWire.write(SIGNAL_PATH_RESET_ADDRESS);
            MpuWire.write(signalPathResetValue);
            MpuWire.endTransmission(true);
          } else {
            firstLog.Log("Number of bytes read from the gyroReset method is not the requested amount", Severity::ERROR);
          }
        } else {
          firstLog.Log("gyrometer reset write (0) operation failed", Severity::ERROR);
        }
      }
    } else {
      firstLog.Log("MPU gyroscope reset operation failed (check begin function)", Severity::ERROR);
      return;
    }
  }

  void configAccel(bool x, bool y) {
    if (isMpuReady && whoAreYou) {
      int storeTransmission;
      uint8_t CONFIG_ACCEL_MASK = (1 << 3) | (1 << 4);
      uint8_t CONFIG_ACCEL_VALUE = (x << 3) | (y << 4);
      MpuWire.beginTransmission(MPU_ADDRESS);
      MpuWire.write(ACCEL_CONFIG_ADDRESS);
      storeTransmission = MpuWire.endTransmission(false);
      if (storeTransmission == 0) {
        int storeRequest;
        storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 1);
        if (storeRequest == 1) {
          accelConfigValue = (MpuWire.read() & ~CONFIG_ACCEL_MASK) | CONFIG_ACCEL_VALUE;
          MpuWire.beginTransmission(MPU_ADDRESS);
          MpuWire.write(ACCEL_CONFIG_ADDRESS);
          MpuWire.write(accelConfigValue);
          MpuWire.endTransmission(true);
        } else {
          firstLog.Log("Number of bytes read from the configAccel method is not the requested amount", Severity::ERROR);
        }
      } else {
        firstLog.Log("accelerometer configuration write operation failed", Severity::ERROR);
      }
    } else{
      firstLog.Log("MPU acceleration configure operation failed (check begin function)", Severity::ERROR);
    }
  }
  void configGyro(bool x, bool y){
    if (isMpuReady && whoAreYou) {
      int storeTransmission;
      uint8_t CONFIG_GYRO_MASK = (1 << 3) | (1 << 4);
      uint8_t CONFIG_GYRO_VALUE = (x << 3) | (y << 4);
      MpuWire.beginTransmission(MPU_ADDRESS);
      MpuWire.write(GYRO_CONFIG_ADDRESS);
      storeTransmission = MpuWire.endTransmission(false);
      if (storeTransmission == 0) {
        int storeRequest;
        storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 1);
        if (storeRequest == 1) {
          gyroConfigValue = (MpuWire.read() & ~CONFIG_GYRO_MASK) | CONFIG_GYRO_VALUE;
          MpuWire.beginTransmission(MPU_ADDRESS);
          MpuWire.write(GYRO_CONFIG_ADDRESS);
          MpuWire.write(gyroConfigValue);
          MpuWire.endTransmission(true);
        } else {
          firstLog.Log("Number of bytes read from the configGyro method is not the requested amount", Severity::ERROR);
        }
      } else {
        firstLog.Log("gyroscope configuration write operation failed", Severity::ERROR);
      }
    } else{
      firstLog.Log("MPU gyroscope configure operation failed (check begin function)", Severity::ERROR);
    }
  }
  std::optional<AccelerometerReading> measureAccel() {
    if (isMpuReady && whoAreYou) {
      int storeTransmission;
      AccelerometerReading Accelerometer;
      uint8_t accel_X_H;
      uint8_t accel_X_L;
      uint8_t accel_Y_H;
      uint8_t accel_Y_L;
      uint8_t accel_Z_H;
      uint8_t accel_Z_L;
      MpuWire.beginTransmission(MPU_ADDRESS);
      MpuWire.write(ACCEL_ADDRESS);
      storeTransmission = MpuWire.endTransmission(false);
      if (storeTransmission == 0) {
        int storeRequest;
        storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 6);
        if (storeRequest < 6) {
          firstLog.Log("Number of bytes read from measureAccel method is below the requested amount", Severity::ERROR);
          return {};
        } else {
          accel_X_H = MpuWire.read();
          accel_X_L = MpuWire.read();
          Accelerometer.x = accel_X_H << 8;
          Accelerometer.x |= accel_X_L;
          accel_Y_H = MpuWire.read();
          accel_Y_L = MpuWire.read();
          Accelerometer.y = accel_Y_H << 8;
          Accelerometer.y |= accel_Y_L;
          accel_Z_H = MpuWire.read();
          accel_Z_L = MpuWire.read();
          Accelerometer.z = accel_Z_H << 8;
          Accelerometer.z |= accel_Z_L;
          return Accelerometer;
        }

      } else {
        firstLog.Log("acceleration read operation failed", Severity::ERROR);
        return {};
      }

    } else {
      firstLog.Log("MPU measure acceleration operation failed (check begin function)", Severity::ERROR);
      return {};
    }
  }

  std::optional<GyroscopeReading> measureGyro() {
    if (isMpuReady && whoAreYou) {
      int storeTransmission;
      GyroscopeReading Gyroscope;
      uint8_t gyro_X_H;
      uint8_t gyro_X_L;
      uint8_t gyro_Y_H;
      uint8_t gyro_Y_L;
      uint8_t gyro_Z_H;
      uint8_t gyro_Z_L;
      MpuWire.beginTransmission(MPU_ADDRESS);
      MpuWire.write(GYRO_ADDRESS);
      storeTransmission = MpuWire.endTransmission(false);
      if (storeTransmission == 0) {
        int storeRequest;
        storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 6);
        if (storeRequest < 6) {
          firstLog.Log("Number of bytes read from measureGyro method is below the requested amount", Severity::ERROR);
          return {};
        } else {
          gyro_X_H = MpuWire.read();
          gyro_X_L = MpuWire.read();
          Gyroscope.x = gyro_X_H << 8;
          Gyroscope.x |= gyro_X_L;
          gyro_Y_H = MpuWire.read();
          gyro_Y_L = MpuWire.read();
          Gyroscope.y = gyro_Y_H << 8;
          Gyroscope.y |= gyro_Y_L;
          gyro_Z_H = MpuWire.read();
          gyro_Z_L = MpuWire.read();
          Gyroscope.z = gyro_Z_H << 8;
          Gyroscope.z |= gyro_Z_L;
          return Gyroscope;
        }
      } else {
        firstLog.Log("gyroscope read operation failed", Severity::ERROR);
        return {};
      }
    } else {
      firstLog.Log("MPU measure gyroscope operation failed (check begin function)", Severity::ERROR);
      return {};
    }
  }
};

MPU6500 FirstMPU(Wire);
std::optional<AccelerometerReading> Accelerometer;
std::optional<GyroscopeReading> Gyroscope;
int16_t ax;
int16_t ay;
int16_t az;
int16_t gx;
int16_t gy;
int16_t gz;
void setup() {
  FirstMPU.firstLog.setLimit(Severity::INFO);
  Wire.begin();
  Serial.begin(9600);
  FirstMPU.begin();
  FirstMPU.sleep(0);
  FirstMPU.cycle(0);
  FirstMPU.configAccel(0, 0);
  FirstMPU.configGyro(0, 0);
}
void loop() {
  if (Accelerometer = FirstMPU.measureAccel(); Accelerometer) {
    Accelerometer->get(ax, ay, az);
    Serial.print("Accelerometer:       ");
    Serial.print(static_cast<double>(ax) / 16324);
    Serial.print("       ");
    Serial.print(static_cast<double>(ay) / 16324);
    Serial.print("       ");
    Serial.println(static_cast<double>(az) / 16324);
  }
  if (Gyroscope = FirstMPU.measureGyro(); Gyroscope) {
    Gyroscope->get(gx, gy, gz);
    Serial.print("Gyroscope:           ");
    Serial.print(static_cast<double>(gx) / 131);
    Serial.print("       ");
    Serial.print(static_cast<double>(gy) / 131);
    Serial.print("       ");
    Serial.println(static_cast<double>(gz) / 131);
  }
  delay(500);
}