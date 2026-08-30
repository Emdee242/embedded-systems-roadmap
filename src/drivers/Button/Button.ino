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
Button Button1(7);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Button1.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(Button1.readPin());
}
