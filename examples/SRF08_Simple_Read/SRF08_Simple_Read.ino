#include <Wire.h>
#include <SRF08.h>

#define SRF08_ADDRESS 0xEA

SRF08 srf08(SRF08_ADDRESS);


void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  Serial.println("Start Demo: Simple Distance Read");
  Serial.print("Version: ");
  int ver = srf08.getVersion();
  Serial.println(ver);  
}

void loop() {
  // put your main code here, to run repeatedly: 
/*  Serial.print("Luminosity: ");
  int luminosity = srf08.getLuminosity();
  Serial.println(luminosity);  */
  Serial.print("Distance: ");
  int distance = srf08.getDistanceCm();
  Serial.print(distance);  
  Serial.println(" Cm.");

  delay(1000);
}
