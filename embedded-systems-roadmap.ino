class LED{
private:
const int pin;
bool isOn = false;
public:
LED(int x) : pin(x){}
void on(){
  digitalWrite(pin, HIGH);
  isOn = true;
}
void off(){
  digitalWrite(pin, LOW);
  isOn = false;
}
void begin() const{
  pinMode(pin, OUTPUT);
}
int getPin() const {return pin;}
bool ledState() const {return isOn;}
};

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

class Timer{
  private:
  unsigned long intervalTime = 0;
  unsigned long recordTime = 0;
  public:
  void reset(){
    recordTime = millis();
  }
  void setTimer(unsigned long x){
    intervalTime = x;
  }
  bool intervalPassed(){
    bool result = false;
    if((millis() - recordTime) >= intervalTime){
      recordTime += intervalTime;
      result = true;
    }
    return result;
  }
};

class Buffer{
private:
constexpr static int size = 16;
int buffArray[size];
int head = 0;
int tail = 0;
uint16_t isArrayFull = 0;
public:
void write(int x){
buffArray[head] = x;
head = (head + 1) & (size - 1);
if(isFull() != size){
isArrayFull++;
}else if (isFull() == size){
tail = (tail + 1) & (size - 1);
  }
}
int read(){
int readVar;
readVar = buffArray[tail];
if(isFull() == 0){
return 0;
}else{
isArrayFull--;
tail = (tail + 1) & (size - 1);
return readVar;
}
}
int isFull() const{
return isArrayFull;
}
};

enum class Severity{
  INFO,
  WARN,
  ERROR
};

LED embedLED(8);
Button embedButton(7);
Debouncer embedDebounce(embedButton);
Timer embedTimer;
Buffer embedBuffer;
void setup(){
embedLED.begin();
embedButton.begin();
Serial.begin(9600);
embedTimer.setTimer(300);
embedTimer.reset();
}
bool buttonPressed = true;
void loop(){
if(embedDebounce.check() == LOW){
if(buttonPressed){
  embedTimer.reset();
  buttonPressed = false;
  embedLED.on();
  embedBuffer.write(1);
}
  if(embedTimer.intervalPassed()){
    if(embedLED.ledState()){
    embedLED.off();
    embedBuffer.write(0);  
    }else{
      embedLED.on();
      embedBuffer.write(1);
    }
  }
}else{
  embedLED.off();
  buttonPressed = true;
}
}