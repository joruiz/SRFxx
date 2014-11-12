/*
 Arduino Library for SRF08 ultrasonic sensor 
 go to http://www.robot-electronics.co.uk/htm/srf08tech.shtml for more information
 
 License: CC BY-SA 3.0: Creative Commons Share-alike 3.0. Feel free 
 to use and abuse this code however you'd like. If you find it useful
 please attribute, and SHARE-ALIKE!
 
 Created July 2013
 by Jonathan Ruiz de Garibay

 */

#include "SRF08.h"
#include <Wire.h>

//
// constructor
//
// This library use I2C protocol so, it is necesary to specified an I2C address.
void SRF08::begin(uint8_t address){

	_address = address >> 1;
	Wire.begin();
}                             

//
// getVersion
//
// Get version of the SRF08 firmware.
uint8_t SRF08::getVersion(){

	Wire.beginTransmission(_address);
	Wire.write(0x00);
	// end I2C transmission
	Wire.endTransmission();

	Wire.requestFrom(_address, (uint8_t)1);
	if (Wire.available() == 1)
		return Wire.read();
	else
		return -1;
}

//
// getLuminosity
//
// get luminosity captured by SRF08 sensor.
uint8_t SRF08::getLuminosity(){

	Wire.beginTransmission(_address);
	Wire.write(0x00);
	Wire.write(INCHES);
	Wire.endTransmission();
	delay(50);

	Wire.beginTransmission(_address);
	Wire.write(LUMINOSITY_ADD);
	Wire.endTransmission();

	Wire.requestFrom(_address, (uint8_t)1);
	if (Wire.available() == 1)
		return Wire.read();
	else
		return -1;
}

//
// setRange
//
// Set rango for distance mesurement
void SRF08::setRange(uint8_t range) {

	Wire.beginTransmission(_address);
	Wire.write(0x02);
	Wire.write(range);
	Wire.endTransmission();
}

//
// getDistanceIn
//
// Get distance captured by SRF08 sensor in inches.
unsigned int SRF08::getDistanceIn(){

	return getDistance(INCHES);
}

//
// getDistanceCm
//
// Get distance captured by SRF08 sensor in centimetres.
unsigned int SRF08::getDistanceCm(){

	return getDistance(CENTIMETRES);
}

//
// getDistanceMs
//
// Get distance captured by SRF08 sensor in miliseconds.
unsigned int SRF08::getDistanceMs(){

	return getDistance(MILISECONDS);
}

//
// changeAddress
//
// Change SRF08 address for new one.
void SRF08::changeAddress(uint8_t newAddress){

	Wire.beginTransmission(_address);
	Wire.write(0x00);
	Wire.write(0xA0);
	Wire.endTransmission();

	Wire.beginTransmission(_address);
	Wire.write(0x00);
	Wire.write(0xAA);
	Wire.endTransmission();

	Wire.beginTransmission(_address);
	Wire.write(0x00);
	Wire.write(0xA5);
	Wire.endTransmission();

	Wire.beginTransmission(_address);
	Wire.write(0x00);
	Wire.write(newAddress);						// New address
	Wire.endTransmission();
}

//
// getDistance
//
// Get distance captured by SRF08 sensor.
unsigned int SRF08::getDistance(uint8_t command){

	int distance = 0, highByte, lowByte; 
  
	Wire.beginTransmission(_address);			// Start communticating with SRF08
	Wire.write(0x00);							// Send Command Byte
	Wire.write(command);						// Send 0x51 to start a ranging
	Wire.endTransmission();
  
	delay(70);									// Wait for ranging to be complete
  
	Wire.beginTransmission(_address);			// start communicating with SRFmodule
	Wire.write(0x02);							// Call the register for start of ranging data
	Wire.endTransmission();
  
	Wire.requestFrom(_address, (uint8_t)2);				// Request 2 bytes from SRF module
	if(Wire.available() == 2)					// Wait for data to arrive
	{
		highByte = Wire.read();					// Get high byte
		lowByte = Wire.read();					// Get low byte

		distance = (highByte << 8) + lowByte;	// Put them together
  
		return(distance);
	}
	else
		return -1;
}