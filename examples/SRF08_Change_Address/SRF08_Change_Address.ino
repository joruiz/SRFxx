#include <Wire.h>
#include <SRF08.h>

#define PRESENT_ADDRESS 0xE0
#define NEW_ADDRESS 0xEA

SRF08 srf08(PRESENT_ADDRESS);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("Start Demo: Change I2C Address");
  Serial.print("SRF08 Version: ");
  int ver = srf08.getVersion();
  Serial.println(ver);  
  
  Serial.print("Previous I2C Address: ");
  Serial.println(PRESENT_ADDRESS, HEX);
  srf08.changeAddress(NEW_ADDRESS);
  Serial.print("New I2C Address: ");
  Serial.println(NEW_ADDRESS, HEX);
}

void loop() {
  // put your main code here, to run repeatedly: 
  delay(100);
}
