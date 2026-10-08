#ifndef SOFTWARETIMER_H
#define SOFTWARETIMER_H
class SoftwareTimer{
  private:
  unsigned long intervalTime = 0;
  unsigned long recordTime = 0;
  public:
  void reset();
  void setTimer(unsigned long x);
  bool intervalPassed();
};
#endif