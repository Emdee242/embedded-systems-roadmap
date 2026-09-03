unsigned long checkSystemTime;
unsigned long checkRefTime = 0;
int ledState = 1;
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
LED led1(7);  
void setup() {
  // put your setup code here, to run once:
led1.begin();

}

void loop() { 
  // put your main code here, to run repeatedly:
checkSystemTime = millis();
if((checkSystemTime - checkRefTime)  >= 500){
  checkRefTime = checkSystemTime;
  if(ledState){
    led1.on();
    ledState = 0;
  }else{
    led1.off();
    ledState = 1;
  }
}
}
