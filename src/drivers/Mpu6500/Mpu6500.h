#ifndef MPU6500_H
#define MPU6500_H
#include "Logger.h"
#include <Wire.h>
#include <optional>
enum class Result {
  SUCCESS,
  INVALID_REG,
  TOO_MANY_BYTES,
  INVALID_SENSOR,
  INVALID_REG_VALUE,
  TIMEOUT,
  NULL_RETURN_TYPE,
  INVALID_REG_LENGTH,
  ERROR
};

struct AccelerometerReading {
private:
  int16_t x;
  int16_t y;
  int16_t z;
  friend class Mpu6500;
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
  friend class Mpu6500;
public:
  void get(int16_t &x1, int16_t &y2, int16_t &z3) const {
    x1 = x;
    y2 = y;
    z3 = z;
  }
};
class Mpu6500 {
private:
  static constexpr uint8_t POWER_MANAGEMENT_REGISTER = 0x6B;
  uint8_t MPU_ADDRESS = 0x68;
  static constexpr uint8_t SIGNAL_PATH_RESET_ADDRESS = 0x68;
  static constexpr uint8_t USER_CONTROL_ADDRESS = 0x6A;
  static constexpr uint8_t ACCEL_CONFIG_ADDRESS = 0x1C;
  static constexpr uint8_t GYRO_CONFIG_ADDRESS = 0x1B;
  static constexpr uint8_t WHO_AM_I_REGISTER = 0x75;
  static constexpr uint8_t GYRO_ADDRESS = 0x43;
  static constexpr uint8_t ACCEL_ADDRESS = 0x3B;
  static constexpr uint8_t WHO_AM_I_VALUE = 0x70;
  bool isMpuReady = false;
  TwoWire &MpuWire;
public:
  Mpu6500(TwoWire &tw);
  Logger firstLog;
  Result begin();
  void setMpuAddress(uint8_t x) {
    MPU_ADDRESS = x;
  }
  Result sleep(bool x);
  Result cycle(bool x);
  Result signalReset(bool x);
  Result accelReset(bool x);
  Result gyroReset(bool x);

  Result configAccel(bool x, bool y);
  Result configGyro(bool x, bool y);
  std::optional<AccelerometerReading> measureAccel();

  std::optional<GyroscopeReading> measureGyro();
};
#endif