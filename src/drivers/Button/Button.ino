class Button{
private:
const uint8_t pin;
public:
Button (uint8_t x) : pin(x){}
void begin() const{
  pinMode(pin, INPUT_PULLUP);
}
bool readPin () const{
  return digitalRead(pin);
}
};
void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}
