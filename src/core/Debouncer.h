#ifndef DEBOUNCER_H
#define DEBOUNCER_H
#include "../drivers/Button.h"
#include <cassert>
class Debouncer {
  private:
    bool initialState = true;
    bool officialState = true;
    bool lastRawRead = true;
    const Button& refButton;
    unsigned long minDebounceTime = 0;
    unsigned long maxDebounceTime = 500;
    unsigned long refBounceTime = 50;
    unsigned long changeDetect = 0;

  public:
    explicit Debouncer(const Button& btn);
    void update();
    bool fall();
    bool lift();
    void setBounceTime(unsigned long x) { 
      refBounceTime = x;
    assert(refBounceTime != minDebounceTime && refBounceTime != maxDebounceTime);
  }
};

#endif
