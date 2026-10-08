void setup(){
Serial.begin(9600);
}
char incomingString;
void loop(){
if(Serial.available()){
  incomingString = Serial.read();
  Serial.print(incomingString);
  if(incomingString == '\n'){
    Serial.println();
  }
}
}
