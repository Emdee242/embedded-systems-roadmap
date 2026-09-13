#include <SPI.h>
SPISettings mySettings(20000000, LSBFIRST, SPI_MODE0);
int WHO_AM_I = 0x75;
int holdData;
void setup(){
  pinMode(8, OUTPUT);
  Serial.begin(9600);
}
void loop(){
SPI.beginTransaction(mySettings);
digitalWrite(8, LOW);
holdData = SPI.transfer(WHO_AM_I);
Serial.println(holdData, HEX);
digitalWrite(8, HIGH);
SPI.endTransaction();
}