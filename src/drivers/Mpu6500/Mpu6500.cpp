#include "Mpu6500.h"
#include "Logger.h"
#include <Wire.h>
#include <optional>

  Mpu6500::Mpu6500(TwoWire &tw)
    : MpuWire(tw){};
  Logger firstLog;
  Result Mpu6500::begin() {
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
          firstLog.Log("Successful", Severity::INFO);
          return Result::SUCCESS;
        } else {
          isMpuReady = false;
          firstLog.Log("Invalid WHO_AM_I value", Severity::ERROR);
          return Result::INVALID_REG_VALUE;
        }
      } else {
        isMpuReady = false;
        firstLog.Log("Number of bytes read from begin method does not match the requested amount", Severity::ERROR);
        return Result::INVALID_REG_LENGTH;
      }
    } else if (storeTransmission == 1) {
      isMpuReady = false;
      firstLog.Log("Data is too long", Severity::ERROR);
      return Result::TOO_MANY_BYTES;
    } else if (storeTransmission == 2) {
      isMpuReady = false;
      firstLog.Log("Invalid device address", Severity::ERROR);
      return Result::INVALID_SENSOR;
    } else if (storeTransmission == 3) {
      isMpuReady = false;
      firstLog.Log("Invalid register address", Severity::ERROR);
      return Result::INVALID_REG;
    } else if (storeTransmission == 4) {
      isMpuReady = false;
      firstLog.Log("Unrecognized error", Severity::ERROR);
      return Result::ERROR;
    } else if (storeTransmission == 5) {
      isMpuReady = false;
      firstLog.Log("Timeout", Severity::ERROR);
      return Result::TIMEOUT;
    } else {
      isMpuReady = false;
      firstLog.Log("non-existing return type, check current endTransmission documentation", Severity::ERROR);
      return Result::NULL_RETURN_TYPE;
    }
  }
  Result Mpu6500::sleep(bool x) {
    if (isMpuReady) {
      int storeTransmission;
      int powerManagementRegisterValue;
      uint8_t SLEEP_MASK = 1 << 6;
      uint8_t SLEEP_VALUE = x << 6;
      MpuWire.beginTransmission(MPU_ADDRESS);
      MpuWire.write(POWER_MANAGEMENT_REGISTER);
      storeTransmission = MpuWire.endTransmission(false);
      if (storeTransmission == 0) {
        int storeRequest;
        storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 1);
        if (storeRequest == 1) {
          powerManagementRegisterValue = (MpuWire.read() & ~SLEEP_MASK) | SLEEP_VALUE;
          MpuWire.beginTransmission(MPU_ADDRESS);
          MpuWire.write(POWER_MANAGEMENT_REGISTER);
          MpuWire.write(powerManagementRegisterValue);
          MpuWire.endTransmission(true);
          return Result::SUCCESS;
        } else {
          firstLog.Log("Number of bytes read from the sleep method is not the requested amount", Severity::ERROR);
          return Result::INVALID_REG_LENGTH;
        }
      } else {
        firstLog.Log("sleep write operation failed", Severity::ERROR);
        return Result::ERROR;
      }
    } else {
      firstLog.Log("MPU sleep operation failed (check begin function)", Severity::ERROR);
      return Result::INVALID_SENSOR;
    }
  }
  Result Mpu6500::cycle(bool x) {
    if (isMpuReady) {
      int storeTransmission;
      int powerManagementRegisterValue;
      uint8_t CYCLE_MASK = 1 << 5;
      uint8_t CYCLE_VALUE = x << 5;
      MpuWire.beginTransmission(MPU_ADDRESS);
      MpuWire.write(POWER_MANAGEMENT_REGISTER);
      storeTransmission = MpuWire.endTransmission(false);
      if (storeTransmission == 0) {
        int storeRequest;
        storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 1);
        if (storeRequest == 1) {
          powerManagementRegisterValue = (MpuWire.read() & ~CYCLE_MASK) | CYCLE_VALUE;
          MpuWire.beginTransmission(MPU_ADDRESS);
          MpuWire.write(POWER_MANAGEMENT_REGISTER);
          MpuWire.write(powerManagementRegisterValue);
          MpuWire.endTransmission(true);
          return Result::SUCCESS;
        } else {
          firstLog.Log("Number of bytes read from the cycle method is not the requested amount", Severity::ERROR);
          return Result::INVALID_REG_LENGTH;
        }

      } else {
        firstLog.Log("MPU cycle write operation failed", Severity::ERROR);
        return Result::ERROR;
      }
    } else {
      firstLog.Log("MPU cycle operation failed (check begin function)", Severity::ERROR);
      return Result::INVALID_SENSOR;
    }
  }
  Result Mpu6500::signalReset(bool x) {
    if (isMpuReady) {
      int storeTransmission;
      int userControlValue;
      uint8_t SIGNAL_RESET_MASK = 1 << 0;
      uint8_t SIGNAL_RESET_VALUE = x << 0;
      MpuWire.beginTransmission(MPU_ADDRESS);
      MpuWire.write(USER_CONTROL_ADDRESS);
      storeTransmission = MpuWire.endTransmission(false);
      if (storeTransmission == 0) {
        int storeRequest;
        storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 1);
        if (storeRequest == 1) {
          userControlValue = (MpuWire.read() & ~SIGNAL_RESET_MASK) | SIGNAL_RESET_VALUE;
          MpuWire.beginTransmission(MPU_ADDRESS);
          MpuWire.write(USER_CONTROL_ADDRESS);
          MpuWire.write(userControlValue);
          MpuWire.endTransmission(true);
          return Result::SUCCESS;
        } else {
          firstLog.Log("Number of bytes read from the generalReset method is not the requested amount", Severity::ERROR);
          return Result::INVALID_REG_LENGTH;
        }

      } else {
        firstLog.Log("general reset write operation failed", Severity::ERROR);
        return Result::ERROR;
      }
    } else {
      firstLog.Log("MPU general reset operation failed (check begin function)", Severity::ERROR);
      return Result::INVALID_SENSOR;
    }
  }
  Result Mpu6500::accelReset(bool x) {
    if (isMpuReady) {
      int storeTransmission;
      int signalPathResetValue;
      uint8_t ACCEL_RESET_MASK = 1 << 1;
      uint8_t ACCEL_RESET_VALUE = x << 1;
      MpuWire.beginTransmission(MPU_ADDRESS);
      MpuWire.write(SIGNAL_PATH_RESET_ADDRESS);
      storeTransmission = MpuWire.endTransmission(false);
      if (storeTransmission == 0) {
        int storeRequest;
        storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 1);
        if (storeRequest == 1) {
          signalPathResetValue = (MpuWire.read() & ~ACCEL_RESET_MASK) | ACCEL_RESET_VALUE;
          MpuWire.beginTransmission(MPU_ADDRESS);
          MpuWire.write(SIGNAL_PATH_RESET_ADDRESS);
          MpuWire.write(signalPathResetValue);
          MpuWire.endTransmission(true);
          return Result::SUCCESS;
        } else {
          firstLog.Log("Number of bytes read from the accelReset method is not the requested amount", Severity::ERROR);
          return Result::INVALID_REG_LENGTH;
        }
      } else {
        firstLog.Log("accelerometer reset write operation failed", Severity::ERROR);
        return Result::ERROR;
      }
    } else {
      firstLog.Log("MPU accelerometer reset operation failed (check begin function)", Severity::ERROR);
      return Result::INVALID_SENSOR;
    }
  }

  Result Mpu6500::gyroReset(bool x) {
    if (isMpuReady) {
      int storeTransmission;
      int signalPathResetValue;
      uint8_t GYRO_RESET_MASK = 1 << 2;
      uint8_t GYRO_RESET_VALUE = x << 2;
      MpuWire.beginTransmission(MPU_ADDRESS);
      MpuWire.write(SIGNAL_PATH_RESET_ADDRESS);
      storeTransmission = MpuWire.endTransmission(false);
      if (storeTransmission == 0) {
        int storeRequest;
        storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 1);
        if (storeRequest == 1) {
          signalPathResetValue = (MpuWire.read() & ~GYRO_RESET_MASK) | GYRO_RESET_VALUE;
          ;
          MpuWire.beginTransmission(MPU_ADDRESS);
          MpuWire.write(SIGNAL_PATH_RESET_ADDRESS);
          MpuWire.write(signalPathResetValue);
          MpuWire.endTransmission(true);
          return Result::SUCCESS;
        } else {
          firstLog.Log("Number of bytes read from the gyroReset method is not the requested amount", Severity::ERROR);
          return Result::INVALID_REG_LENGTH;
        }
      } else {
        firstLog.Log("gyrometer reset write operation failed", Severity::ERROR);
        return Result::ERROR;
      }
    } else {
      firstLog.Log("MPU gyroscope reset operation failed (check begin function)", Severity::ERROR);
      return Result::INVALID_SENSOR;
    }
  }

  Result Mpu6500::configAccel(bool x, bool y) {
    if (isMpuReady) {
      int storeTransmission;
      int accelConfigValue;
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
          return Result::SUCCESS;
        } else {
          firstLog.Log("Number of bytes read from the configAccel method is not the requested amount", Severity::ERROR);
          return Result::INVALID_REG_LENGTH;
        }
      } else {
        firstLog.Log("accelerometer configuration write operation failed", Severity::ERROR);
        return Result::ERROR;
      }
    } else {
      firstLog.Log("MPU acceleration configure operation failed (check begin function)", Severity::ERROR);
      return Result::INVALID_SENSOR;
    }
  }
  Result Mpu6500::configGyro(bool x, bool y) {
    if (isMpuReady) {
      int storeTransmission;
      int gyroConfigValue;
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
          return Result::SUCCESS;
        } else {
          firstLog.Log("Number of bytes read from the configGyro method is not the requested amount", Severity::ERROR);
          return Result::INVALID_REG_LENGTH;
        }
      } else {
        firstLog.Log("gyroscope configuration write operation failed", Severity::ERROR);
        return Result::ERROR;
      }
    } else {
      firstLog.Log("MPU gyroscope configure operation failed (check begin function)", Severity::ERROR);
      return Result::INVALID_SENSOR;
    }
  }
  std::optional<AccelerometerReading> Mpu6500::measureAccel() {
    if (isMpuReady) {
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

  std::optional<GyroscopeReading> Mpu6500::measureGyro() {
    if (isMpuReady) {
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