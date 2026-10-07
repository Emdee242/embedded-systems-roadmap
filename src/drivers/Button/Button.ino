#include <Button.h>
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
