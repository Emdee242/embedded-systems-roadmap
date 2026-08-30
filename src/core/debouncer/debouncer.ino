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
bool initialState = HIGH;
bool officialState = HIGH;
bool transition = HIGH;
const Button& refButton;
unsigned long refBounceTime = 50;
unsigned long changeDetect = 0;
  public:
  Debouncer(const Button& btn) : refButton(btn){};
  bool check(){
    bool tempReadState = refButton.readPin();
    if(initialState != tempReadState){
      changeDetect = millis();
    }
    if((millis() - changeDetect) >= refBounceTime){
      if(officialState != tempReadState){
        officialState = tempReadState;
      }
    }
    initialState = tempReadState;
   return officialState; 
  }
  bool fall(){
  bool triggered = LOW;
  int recentTransition = check();
  if(transition == HIGH && recentTransition == LOW){
    triggered = true;
  }
  transition = recentTransition;
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
Serial.print(Debouncer1.check());

}
