#include <iostream>
enum class Severity{
  INFO,
  WARN,
  ERROR
};
void Log(const char* message, Severity Level){
Serial.print(message); Serial.print("      ");
switch(Level){
  case(Severity::INFO):
Serial.println("INFO");
break;
case(Severity::WARN):
Serial.println("WARN");
  break;
case(Severity::ERROR):
Serial.println("ERROR");
  break;
  default:
  std::cout << "Invalid input";
  break;
}
}
void setup(){
pinMode(7, INPUT);
}
void loop(){
if(digitalRead(7) == HIGH){
Log("Sensor noise detected", Severity::WARN);   // This whole if statement is just for demonstration.. holding the button doesn't translate to sensor noise
}
}