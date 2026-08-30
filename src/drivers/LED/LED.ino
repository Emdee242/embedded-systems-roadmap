unsigned long checkSystemTime;
unsigned long checkRefTime = 0;
int ledState = 1;
class LED{
private:
const int pin;
public:
LED(int x) : pin(x){}
void on(){
  digitalWrite(getPin(), HIGH);
}
void off(){
  digitalWrite(getPin(), LOW);
}
void setMode(int x){
  pinMode(getPin(), x);
}

int getPin() const {return pin;}
};
LED led1(7);  
void setup() {
  // put your setup code here, to run once:
led1.setMode(OUTPUT);

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
