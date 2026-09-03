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
class Debouncer{
  private:
bool initialState = true;
bool officialState = true;
bool lastRawRead = true;
const Button& refButton;
unsigned long refBounceTime = 50;
unsigned long changeDetect = 0;
  public:
  Debouncer(const Button& btn) : refButton(btn){};
  void update(){
    initialState = officialState;
    bool tempReadState = refButton.readPin();
    if(lastRawRead != tempReadState){
      changeDetect = millis();
    }
    if((millis() - changeDetect) >= refBounceTime){
      officialState = tempReadState;
    }
    lastRawRead = tempReadState;
  }
  bool fall(){
  bool triggered = false;
  if(initialState == HIGH && officialState == LOW){
    triggered = true;
  }
  return triggered;
  }
};
Button Button1(7);
Debouncer Debouncer1(Button1);
void setup(){
Serial.begin(9600);
Button1.begin();
}
void loop(){
Debouncer1.update();
if(Debouncer1.fall()){
  Serial.println(1);
}
}
