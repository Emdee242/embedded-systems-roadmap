#ifndef MPU6500_H
#define MPU6500_H
#include "../core/Logger.h"
#include <Wire.h>
#include <cstdint>
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
    int16_t x{};
    int16_t y{};
    int16_t z{};
    float aX{};
    float aY{};
    float aZ{};
    friend class Mpu6500;

  public:
    void get(float& x1, float& y2, float& z3) const {
        x1 = aX;
        y2 = aY;
        z3 = aZ;
    }
};
struct GyroscopeReading {
  private:
    int16_t x{};
    int16_t y{};
    int16_t z{};
    float gX{};
    float gY{};
    float gZ{};
    friend class Mpu6500;

  public:
    void get(float& x1, float& y2, float& z3) const {
        x1 = gX;
        y2 = gY;
        z3 = gZ;
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
    float accelConfigRate = 16384;
    float gyroConfigRate = 131;
    bool isMpuReady = false;
    TwoWire& MpuWire;
    Result beginWrite(uint8_t registerAddress);
    std::optional<uint8_t> read();
    void write(uint8_t registerAddress, std::optional<uint8_t> registerValue, uint8_t value, uint8_t mask);
  public:
    explicit Mpu6500(TwoWire& tw);
    Logger firstLog;
    Result begin();
    void setMpuAddress(uint8_t x) { MPU_ADDRESS = x; }
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