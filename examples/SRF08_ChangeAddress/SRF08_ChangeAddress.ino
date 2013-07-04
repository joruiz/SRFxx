/*
  ChangeAddress
  Change SRF08 I2C address.
 
  This example code is in the public domain.
 */
 
#include <Wire.h>
#include <SRF08.h>

#define PRESENT_ADDRESS 0xE0
#define NEW_ADDRESS 0xEA

SRF08 srf08;

void setup() {

  Serial.begin(9600);
  Serial.println("Start Demo: Change I2C Address");
  
  srf08.begin(PRESENT_ADDRESS);
  
  Serial.print("Previous I2C Address: ");
  Serial.println(PRESENT_ADDRESS, HEX);
  srf08.changeAddress(NEW_ADDRESS);
  Serial.print("New I2C Address: ");
  Serial.println(NEW_ADDRESS, HEX);
}

void loop() {

  delay(100);
}
