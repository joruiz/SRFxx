/*
 Arduino Library for SRF08 ultrasonic sensor 
 go to http://www.robot-electronics.co.uk/htm/srf08tech.shtml for more information
 
 License: CC BY-SA 3.0: Creative Commons Share-alike 3.0. Feel free 
 to use and abuse this code however you'd like. If you find it useful
 please attribute, and SHARE-ALIKE!
 
 Created July 2013
 by Jonathan Ruiz de Garibay

 */ 

#ifndef SRF08_h
#define SRF08_h

#include "Arduino.h"

#define INCHES			0x50
#define CENTIMETRES		0x51
#define MILISECONDS		0x52

#define LUMINOSITY_ADD	0x01

class SRF08
{
	public:
		void begin(uint8_t address);
		uint8_t getVersion();
		uint8_t getLuminosity();
		void setRange(uint8_t range);
		unsigned int getDistanceIn();
		unsigned int getDistanceCm();
		unsigned int getDistanceMs();
		void changeAddress(uint8_t newAddress);

	private:
		uint8_t _address;
		unsigned int getDistance(uint8_t command);
};

#endif