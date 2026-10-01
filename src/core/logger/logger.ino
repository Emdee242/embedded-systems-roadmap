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
Logger testLog;
void setup(){
pinMode(7, INPUT);
testLog.setLimit(Severity::INFO);
}
void loop(){
if(digitalRead(7) == HIGH){
testLog.Log("Sensor noise detected", Severity::WARN);   // This whole if statement is just for demonstration.. holding the button doesn't translate to sensor noise
}
}