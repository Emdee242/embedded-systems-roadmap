#ifndef LOGGER_H
#define LOGGER_H
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
enum class Severity {
    INFO,
    WARN,
    ERROR

};
class Logger {
  private:
    Severity maxLogger = Severity::INFO;

  public:
    SemaphoreHandle_t LogMutex = xSemaphoreCreateMutex();
    void setLimit(Severity Level);
    void Log(const char* message, Severity Level);
};
#endif