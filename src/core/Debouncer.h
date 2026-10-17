#ifndef DEBOUNCER_H
#define DEBOUNCER_H
#include "../drivers/Button.h"
class Debouncer {
  private:
    bool initialState = true;
    bool officialState = true;
    bool lastRawRead = true;
    const Button& refButton;
    static constexpr unsigned long minDebounceTime = 0;
    static constexpr unsigned long maxDebounceTime = 500;
    static constexpr unsigned long refBounceTime = 50;
    static_assert(refBounceTime != minDebounceTime && refBounceTime != maxDebounceTime);;
    unsigned long changeDetect = 0;

  public:
    explicit Debouncer(const Button& btn);
    void update();
    bool fall();
    bool lift();
    void setBounceTime(unsigned long x) { refBounceTime = x; }
};

#endif
