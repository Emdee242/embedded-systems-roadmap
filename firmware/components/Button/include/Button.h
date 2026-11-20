#ifndef BUTTON_H
#define BUTTON_H
class Button {
  private:
    const uint8_t pin;
    const uint64_t mask;
  public:
    explicit Button(uint8_t x);
    void begin() const;
    bool readPin() const;
};
#endif