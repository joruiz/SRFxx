/*
  ReadLuminosity
  Read luminosity in percentage.
 
  This example code is in the public domain.
 */
 
#include <Wire.h>
#include "SRF08.h"

#define SRF08_ADDRESS 0xE0

SRF08 srf08;

void setup() {
  
  Serial.begin(9600);
  Serial.println("Start Demo: Simple Distance Read");
  
  srf08.begin(SRF08_ADDRESS);
  Serial.print("Version: ");
  int ver = srf08.getVersion();
  Serial.println(ver);  
}

void loop() {

  Serial.print("Luminosity: ");
  int limunosity = srf08.getLuminosity();
  Serial.print(limunosity * 100 / 255);  
  Serial.println(" %");
  delay(1000);
}
