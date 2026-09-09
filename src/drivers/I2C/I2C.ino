void setup(){
Serial.begin(9600);
Wire.begin();
}
void loop(){
int wire = 0x75;
int mpuAddress = 0x68;
int consoleOutput;
Wire.beginTransmission(mpuAddress);
Wire.requestFrom(mpuAddress, wire);
consoleOutput = Wire.read();
Serial.print(consoleOutput);
}
