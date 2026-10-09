#ifndef DEBOUNCER_H
#define DEBOUNCER_H
#include <Button.h>
enum class State {
  IDLE,
  CHECKING
};
class Debouncer {
private:
  bool initialState = true;
  bool officialState = true;
  bool lastRawRead = true;
  const Button& refButton;
  State currentState;
  unsigned long refBounceTime = 50;
  unsigned long changeDetect = 0;
public:
  Debouncer(const Button& btn);
  void update();
  bool fall();
  void setBounceTime(unsigned long x) {
    refBounceTime = x;
  }
  State returnState() const {
    return currentState;
  }
};

#endif
