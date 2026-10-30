#include "ProcessTask.h"
#include "../Application.h"
#include "../../drivers/Mpu6500.h"
static void processTaskEntry(void *parameters){
for(;;){
    Application *ProcessApplication = static_cast<Application*>(parameters);
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
                AccelBuffer.write(ax);
                AccelBuffer.write(ay);
                AccelBuffer.write(az);
            }
            if (Gyroscope = CoreMPU.measureGyro(); Gyroscope) {
                float gx;
                float gy;
                float gz;
                GyroBuffer.write(gx);
                GyroBuffer.write(gy);
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
}
