unsigned long checkSystemTime;
unsigned long checkRefTime = 0;
int ledState = 1;
class LED{
private:
int pin;
public:
void on(){
  digitalWrite(pin, HIGH);
}
void off(){
  digitalWrite(pin, LOW);
}
LED(int x){
pin = x;
}
int getPin(){return pin;}
};
LED led1(7);  
void setup() {
  // put your setup code here, to run once:
pinMode(led1.getPin(), OUTPUT);

}

void loop() { 
  // put your main code here, to run repeatedly:
checkSystemTime = millis();
if((checkSystemTime - checkRefTime)  > 500){
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
