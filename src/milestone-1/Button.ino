class Button{
private:
const int pin;
public:
void Button const(int x): pin(x){}
int begin(){
  pinMode(pin, INPUT_PULLUP);
}
int readPin(){
  return digitalRead(pin);
}
};
void setup() {
  // put your setup code here, to run once:
Button Button1(7);
}

void loop() {
  // put your main code here, to run repeatedly:

}
