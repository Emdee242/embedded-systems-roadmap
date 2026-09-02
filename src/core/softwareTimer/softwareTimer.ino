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
constexpr unsigned long specificTimer = 1000;
Timer Timer1(specificTimer);
void setup(){
  
}
void loop(){

}