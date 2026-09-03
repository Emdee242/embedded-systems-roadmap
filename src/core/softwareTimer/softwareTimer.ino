class Timer{
  private:
  unsigned long intervalTime = 0;
  unsigned long recordTime = 0;
  public:
  void reset(){
    recordTime = millis();
  }
  void setTimer(unsigned long x){
    intervalTime = x;
  }
  bool intervalPassed(){
    bool result = false;
    if((millis() - recordTime) >= intervalTime){
      recordTime += intervalTime;
      result = true;
    }
    return result;
  }
};
const unsigned long specificTimer = 1000;
Timer sensorTimer;
void setup(){
Serial.begin(9600);
sensorTimer.setTimer(specificTimer);
sensorTimer.reset();
}
void loop(){
if(sensorTimer.intervalPassed()){
  Serial.println(1);
}
}