class Timer{
  private:
  constexpr unsigned long intervalTime;
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
void setup(){
  
}
void loop(){

}