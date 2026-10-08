#include <SPI.h>
SPISettings mySettings(1000000, MSBFIRST, SPI_MODE0);
int idRegister = 0xD0;
int holdData;
void setup(){
  pinMode(8, OUTPUT);
  SPI.begin();
  Serial.begin(9600);
}
void loop(){
SPI.beginTransaction(mySettings);
digitalWrite(8, LOW);
SPI.transfer(idRegister | 0x80);
holdData = SPI.transfer(0x00);
Serial.println(holdData, HEX);
digitalWrite(8, HIGH);
SPI.endTransaction();
}