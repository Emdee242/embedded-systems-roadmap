#include "Application.h"
#include "../core/CircularBuffer.h"
#include "../core/Debouncer.h"
#include "../core/SoftwareTimer.h"
#include "../drivers/Button.h"
#include "../drivers/Mpu6500.h"
#include <Wire.h>
void Application::start() {
    Wire.begin();
    Serial.begin(115200);
    CoreButton.begin();
    CoreTimer.reset();
    CoreTimer.setTimer(readInterval);
    CoreMPU.begin();
    CoreMPU.sleep(0);
    CoreMPU.cycle(0);
    CoreMPU.configAccel(0, 0);
    CoreMPU.configGyro(0, 0);
    CoreMPU.firstLog.setLimit(Severity::INFO);
}
void Application::update() {
    CoreDebouncer.update();
    if (CoreTimer.intervalPassed()) {
        switch (ApplicationState) {
        case (CurrentState::ACTIVE):
            if (CoreDebouncer.lift()) {
                ApplicationState = CurrentState::IDLE;
            }
            if (Accelerometer = CoreMPU.measureAccel(); Accelerometer) {
                float ax;
                float ay;
                float az;
                Accelerometer->get(ax, ay, az);
                Serial.print("Accelerometer:       ");
                Serial.print(ax);
                AccelBuffer.write(ax);
                Serial.print("       ");
                Serial.print(ay);
                AccelBuffer.write(ay);
                Serial.print("       ");
                Serial.println(az);
                AccelBuffer.write(az);
            }
            if (Gyroscope = CoreMPU.measureGyro(); Gyroscope) {
                float gx;
                float gy;
                float gz;
                Gyroscope->get(gx, gy, gz);
                Serial.print("Gyroscope:           ");
                Serial.print(gx);
                GyroBuffer.write(gx);
                Serial.print("       ");
                Serial.print(gy);
                GyroBuffer.write(gy);
                Serial.print("       ");
                Serial.println(gz);
                GyroBuffer.write(gz);
            }
            break;
        case (CurrentState::IDLE):
            if (CoreDebouncer.fall()) {
                ApplicationState = CurrentState::ACTIVE;
            }
            Serial.println("----------------------");
            break;
        default:
            Serial.println(".........................");
            break;
        }
    }
}