class Timer{
  private:
  const unsigned long intervalTime;
  unsigned long recordTime = 0;
  public:
  Timer (unsigned long x) : intervalTime(x){}
  bool interval(){
    bool result = false;
    if((millis() - recordTime) >= intervalTime){
      recordTime = millis();
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