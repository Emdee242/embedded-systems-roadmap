  #include "Logger.h"
  #include <Arduino.h>
  void Logger::setLimit(Severity Level) {
    maxLogger = Level;
  }
  void Logger::Log(const char *message, Severity Level) {

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
    }
  }
