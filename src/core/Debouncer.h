#ifndef DEBOUNCER_H
#define DEBOUNCER_H
#include "../drivers/Button.h"
class Debouncer {
  private:
    bool initialState = true;
    bool officialState = true;
    bool lastRawRead = true;
    const Button& refButton;
    unsigned long refBounceTime = 50;
    unsigned long changeDetect = 0;

  public:
    explicit Debouncer(const Button& btn);
    void update();
    bool fall();
    bool lift();
    void setBounceTime(unsigned long x) { refBounceTime = x; }
};

#endif
