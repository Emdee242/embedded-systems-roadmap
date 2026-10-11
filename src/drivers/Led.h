#ifndef LED_H
#define LED_H
class Led{
private:
const int pin;
bool isOn = false;
public:
Led(int x);
void on();
void off();
void begin() const;
int getPin() const {return pin;}
bool ledState() const {return isOn;}
};
#endif