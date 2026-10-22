#include "Mpu6500.h"
#include "../core/Logger.h"
#include <Wire.h>
#include <cstdint>
#include <optional>
Mpu6500::Mpu6500(TwoWire& tw) : MpuWire(tw){};
Logger firstLog;
Result Mpu6500::beginWrite(uint8_t registerAddress) {
    MpuWire.beginTransmission(MPU_ADDRESS);
    MpuWire.write(registerAddress);
    int storeTransmission = MpuWire.endTransmission(false);
    if (storeTransmission == 0) {
        return Result::SUCCESS;
    } else if (storeTransmission == 1) {
        return Result::TOO_MANY_BYTES;
    } else if (storeTransmission == 2) {
        return Result::INVALID_SENSOR;
    } else if (storeTransmission == 3) {
        return Result::INVALID_REG;
    } else if (storeTransmission == 4) {
        return Result::ERROR;
    } else if (storeTransmission == 5) {
        return Result::TIMEOUT;
    } else {
        return Result::NULL_RETURN_TYPE;
    }
}
std::optional<uint8_t> Mpu6500::read() {
    int storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 1);
    if (storeRequest == 1) {
        int registerValue = MpuWire.read();
        return registerValue;
    } else {
        return {};
    }
}
void Mpu6500::write(uint8_t registerAddress,
                    std::optional<uint8_t> registerValue, uint8_t value,
                    uint8_t mask) {
    if (registerValue) {
        uint8_t writeValue = (*registerValue & ~mask) | value;
        MpuWire.beginTransmission(MPU_ADDRESS);
        MpuWire.write(registerAddress);
        MpuWire.write(writeValue);
        MpuWire.endTransmission(true);
    }
}
Result Mpu6500::begin() {
    Result tempResult = beginWrite(WHO_AM_I_REGISTER);
    if (tempResult == Result::SUCCESS) {
        std::optional<int> tempRead = read();
        if (tempRead) {
            if (tempRead == WHO_AM_I_VALUE) {
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
            firstLog.Log("Number of bytes read from begin method does not "
                         "match the requested amount",
                         Severity::ERROR);
            return Result::INVALID_REG_LENGTH;
        }
    } else if (tempResult == Result::TOO_MANY_BYTES) {
        isMpuReady = false;
        firstLog.Log("Data is too long", Severity::ERROR);
        return Result::TOO_MANY_BYTES;
    } else if (tempResult == Result::INVALID_SENSOR) {
        isMpuReady = false;
        firstLog.Log("Invalid device address", Severity::ERROR);
        return Result::INVALID_SENSOR;
    } else if (tempResult == Result::INVALID_REG) {
        isMpuReady = false;
        firstLog.Log("Invalid register address", Severity::ERROR);
        return Result::INVALID_REG;
    } else if (tempResult == Result::ERROR) {
        isMpuReady = false;
        firstLog.Log("Unrecognized error", Severity::ERROR);
        return Result::ERROR;
    } else if (tempResult == Result::TIMEOUT) {
        isMpuReady = false;
        firstLog.Log("Timeout", Severity::ERROR);
        return Result::TIMEOUT;
    } else {
        isMpuReady = false;
        firstLog.Log("non-existing return type, check current endTransmission "
                     "documentation",
                     Severity::ERROR);
        return Result::NULL_RETURN_TYPE;
    }
}
Result Mpu6500::sleep(bool x) {
    if (isMpuReady) {
        Result tempResult;
        tempResult = beginWrite(POWER_MANAGEMENT_REGISTER);
        if (tempResult == Result::SUCCESS) {
            std::optional<int> tempRead;
            uint8_t SLEEP_MASK = 1 << 6;
            uint8_t value = x * SLEEP_MASK;
            tempRead = read();
            if (tempRead) {
                write(POWER_MANAGEMENT_REGISTER, tempRead, value, SLEEP_MASK);
                return Result::SUCCESS;
            } else {
                firstLog.Log("Number of bytes read from the sleep method is "
                             "not the requested amount",
                             Severity::ERROR);
                return Result::INVALID_REG_LENGTH;
            }
        } else {
            firstLog.Log("sleep write operation failed", Severity::ERROR);
            return Result::ERROR;
        }
    } else {
        firstLog.Log("MPU sleep operation failed (check begin function)",
                     Severity::ERROR);
        return Result::INVALID_SENSOR;
    }
}
Result Mpu6500::cycle(bool x) {
    if (isMpuReady) {
        Result tempResult;
        tempResult = beginWrite(POWER_MANAGEMENT_REGISTER);
        if (tempResult == Result::SUCCESS) {
            std::optional<int> tempRead;
            uint8_t CYCLE_MASK = 1 << 5;
            uint8_t value = x * CYCLE_MASK;
            tempRead = read();
            if (tempRead) {
                write(POWER_MANAGEMENT_REGISTER, tempRead, value, CYCLE_MASK);
                return Result::SUCCESS;
            } else {
                firstLog.Log("Number of bytes read from the cycle method is "
                             "not the requested amount",
                             Severity::ERROR);
                return Result::INVALID_REG_LENGTH;
            }
        } else {
            firstLog.Log("MPU cycle write operation failed", Severity::ERROR);
            return Result::ERROR;
        }
    } else {
        firstLog.Log("MPU cycle operation failed (check begin function)",
                     Severity::ERROR);
        return Result::INVALID_SENSOR;
    }
}
Result Mpu6500::signalReset(bool x) {
    if (isMpuReady) {
        Result tempResult;
        tempResult = beginWrite(USER_CONTROL_ADDRESS);
        if (tempResult == Result::SUCCESS) {
            std::optional<int> tempRead;
            uint8_t SIGNAL_RESET_MASK = 1 << 0;
            uint8_t value = x * SIGNAL_RESET_MASK;
            tempRead = read();
            if (tempRead) {
                write(USER_CONTROL_ADDRESS, tempRead, value, SIGNAL_RESET_MASK);
                return Result::SUCCESS;
            } else {
                firstLog.Log("Number of bytes read from the generalReset "
                             "method is not the requested amount",
                             Severity::ERROR);
                return Result::INVALID_REG_LENGTH;
            }
        } else {
            firstLog.Log("general reset write operation failed",
                         Severity::ERROR);
            return Result::ERROR;
        }
    } else {
        firstLog.Log(
            "MPU general reset operation failed (check begin function)",
            Severity::ERROR);
        return Result::INVALID_SENSOR;
    }
}
Result Mpu6500::accelReset(bool x) {
    if (isMpuReady) {
        Result tempResult;
        tempResult = beginWrite(SIGNAL_PATH_RESET_ADDRESS);
        if (tempResult == Result::SUCCESS) {
            std::optional<int> tempRead;
            uint8_t ACCEL_RESET_MASK = 1 << 1;
            uint8_t value = x * ACCEL_RESET_MASK;
            tempRead = read();
            if (tempRead) {
                write(SIGNAL_PATH_RESET_ADDRESS, tempRead, value,
                      ACCEL_RESET_MASK);
                return Result::SUCCESS;
            } else {
                firstLog.Log("Number of bytes read from the accelReset method "
                             "is not the requested amount",
                             Severity::ERROR);
                return Result::INVALID_REG_LENGTH;
            }
        } else {
            firstLog.Log("accelerometer reset write operation failed",
                         Severity::ERROR);
            return Result::ERROR;
        }
    } else {
        firstLog.Log(
            "MPU accelerometer reset operation failed (check begin function)",
            Severity::ERROR);
        return Result::INVALID_SENSOR;
    }
}

Result Mpu6500::gyroReset(bool x) {
    if (isMpuReady) {
        Result tempResult;
        tempResult = beginWrite(SIGNAL_PATH_RESET_ADDRESS);
        if (tempResult == Result::SUCCESS) {
            std::optional<int> tempRead;
            uint8_t GYRO_RESET_MASK = 1 << 2;
            uint8_t value = x * GYRO_RESET_MASK;
            tempRead = read();
            if (tempRead) {
                write(SIGNAL_PATH_RESET_ADDRESS, tempRead, value,
                      GYRO_RESET_MASK);
                return Result::SUCCESS;
            } else {
                firstLog.Log("Number of bytes read from the gyroReset method "
                             "is not the requested amount",
                             Severity::ERROR);
                return Result::INVALID_REG_LENGTH;
            }
        } else {
            firstLog.Log("gyrometer reset write operation failed",
                         Severity::ERROR);
            return Result::ERROR;
        }
    } else {
        firstLog.Log(
            "MPU gyroscope reset operation failed (check begin function)",
            Severity::ERROR);
        return Result::INVALID_SENSOR;
    }
}

Result Mpu6500::configAccel(bool x, bool y) {
    if (isMpuReady) {
        uint8_t configRate = (x << 1) | y;
        switch (configRate) {
        case (0):
            accelConfigRate = 16384;
            break;
        case (1):
            accelConfigRate = 8192;
            break;
        case 3:
            accelConfigRate = 4096;
            break;
        case 4:
            accelConfigRate = 2048;
            break;
        default:
            accelConfigRate = 16384;
            break;
        }
        Result tempResult;
        tempResult = beginWrite(ACCEL_CONFIG_ADDRESS);
        if (tempResult == Result::SUCCESS) {
            std::optional<int> tempRead;
            uint8_t CONFIG_ACCEL_MASK = (1 << 3) | (1 << 4);
            uint8_t CONFIG_ACCEL_VALUE = (y << 3) | (x << 4);
            tempRead = read();
            if (tempRead) {
                write(ACCEL_CONFIG_ADDRESS, tempRead, CONFIG_ACCEL_VALUE,
                      CONFIG_ACCEL_MASK);
                return Result::SUCCESS;
            } else {
                firstLog.Log("Number of bytes read from the configAccel method "
                             "is not the requested amount",
                             Severity::ERROR);
                return Result::INVALID_REG_LENGTH;
            }
        } else {
            firstLog.Log("accelerometer configuration write operation failed",
                         Severity::ERROR);
            return Result::ERROR;
        }
    } else {
        firstLog.Log("MPU acceleration configure operation failed (check begin "
                     "function)",
                     Severity::ERROR);
        return Result::INVALID_SENSOR;
    }
}
Result Mpu6500::configGyro(bool x, bool y) {
    if (isMpuReady) {
        uint8_t configRate = (x << 1) | y;
        switch (configRate) {
        case (0):
            gyroConfigRate = 131;
            break;
        case (1):
            gyroConfigRate = 65.5;
            break;
        case 3:
            gyroConfigRate = 32.8;
            break;
        case 4:
            gyroConfigRate = 16.4;
            break;
        default:
            gyroConfigRate = 131;
            break;
        }
        Result tempResult;
        tempResult = beginWrite(GYRO_CONFIG_ADDRESS);
        if (tempResult == Result::SUCCESS) {
            std::optional<int> tempRead;
            uint8_t CONFIG_GYRO_MASK = (1 << 3) | (1 << 4);
            uint8_t CONFIG_GYRO_VALUE = (y << 3) | (x << 4);
            tempRead = read();
            if (tempRead) {
                write(GYRO_CONFIG_ADDRESS, tempRead, CONFIG_GYRO_VALUE,
                      CONFIG_GYRO_MASK);
                return Result::SUCCESS;
            } else {
                firstLog.Log("Number of bytes read from the configGyro method "
                             "is not the requested amount",
                             Severity::ERROR);
                return Result::INVALID_REG_LENGTH;
            }
        } else {
            firstLog.Log("gyroscope configuration write operation failed",
                         Severity::ERROR);
            return Result::ERROR;
        }
    } else {
        firstLog.Log(
            "MPU gyroscope configure operation failed (check begin function)",
            Severity::ERROR);
        return Result::INVALID_SENSOR;
    }
}
std::optional<AccelerometerReading> Mpu6500::measureAccel() {
    if (isMpuReady) {
        Result tempResult = beginWrite(ACCEL_ADDRESS);
        if (tempResult == Result::SUCCESS) {
            AccelerometerReading Accelerometer;
            int storeRequest;
            storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 6);
            if (storeRequest < 6) {
                firstLog.Log("Number of bytes read from measureAccel method is "
                             "below the requested amount",
                             Severity::ERROR);
                return {};
            } else {
                uint8_t accel_X_H;
                uint8_t accel_X_L;
                uint8_t accel_Y_H;
                uint8_t accel_Y_L;
                uint8_t accel_Z_H;
                uint8_t accel_Z_L;
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
                Accelerometer.aX = Accelerometer.x / accelConfigRate;
                Accelerometer.aY = Accelerometer.y / accelConfigRate;
                Accelerometer.aZ = Accelerometer.z / accelConfigRate;
                return Accelerometer;
            }

        } else {
            firstLog.Log("acceleration read operation failed", Severity::ERROR);
            return {};
        }

    } else {
        firstLog.Log(
            "MPU measure acceleration operation failed (check begin function)",
            Severity::ERROR);
        return {};
    }
}

std::optional<GyroscopeReading> Mpu6500::measureGyro() {
    if (isMpuReady) {
        Result tempResult = beginWrite(ACCEL_ADDRESS);
        if (tempResult == Result::SUCCESS) {
            GyroscopeReading Gyroscope;
            int storeRequest;
            storeRequest = MpuWire.requestFrom(MPU_ADDRESS, 6);
            if (storeRequest < 6) {
                firstLog.Log("Number of bytes read from measureGyro method is "
                             "below the requested amount",
                             Severity::ERROR);
                return {};
            } else {
                uint8_t gyro_X_H;
                uint8_t gyro_X_L;
                uint8_t gyro_Y_H;
                uint8_t gyro_Y_L;
                uint8_t gyro_Z_H;
                uint8_t gyro_Z_L;
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
                Gyroscope.gX = Gyroscope.x / gyroConfigRate;
                Gyroscope.gY = Gyroscope.y / gyroConfigRate;
                Gyroscope.gZ = Gyroscope.z / gyroConfigRate;
                return Gyroscope;
            }
        } else {
            firstLog.Log("gyroscope read operation failed", Severity::ERROR);
            return {};
        }
    } else {
        firstLog.Log(
            "MPU measure gyroscope operation failed (check begin function)",
            Severity::ERROR);
        return {};
    }
}