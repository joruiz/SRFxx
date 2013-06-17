#include "Wire.h"
#include "SRF08.h"

int _address;

SRF08::SRF08(uint8_t address){

	_address = address >> 1;
	Wire.begin();
}                             

int SRF08::getVersion(){

	Wire.beginTransmission(_address);
	Wire.write(0x00); // posición de comandos
	// end I2C transmission
	Wire.endTransmission();

	Wire.requestFrom(_address, 1);
	if (Wire.available() == 1)
		return Wire.read();
	else
		return -1;
}

int SRF08::getLuminosity(){

	Wire.beginTransmission(_address);
	Wire.write(0x00); // posición de comandos
	Wire.write(0x50); // número de bytes del comando
	// end I2C transmission
	Wire.endTransmission();
	delay(100);

	Wire.beginTransmission(_address);             // start communicating with SRFmodule
	Wire.write(0x01);                           // Call the register for start of ranging data
	Wire.endTransmission();

	Wire.requestFrom(_address, 2);
	if (Wire.available() == 1)
		return Wire.read();	//se descarta este primer dato de la versión
	else
		return -1;
}

int SRF08::getDistanceIn(){

	return getDistance(0x50);
}

int SRF08::getDistanceCm(){

	return getDistance(0x51);
}

int SRF08::getDistanceMs(){

	return getDistance(0x52);
}

void SRF08::changeAddress(int newAddress){

	Wire.beginTransmission(_address);
	Wire.write(0x00); // posición de comandos
	Wire.write(0xA0); // primer comando
	Wire.endTransmission();

	Wire.beginTransmission(_address);
	Wire.write(0x00); // posición de comandos
	Wire.write(0xAA); // segundo comando
	Wire.endTransmission();

	Wire.beginTransmission(_address);
	Wire.write(0x00); // posición de comandos
	Wire.write(0xA5); // tercer comando
	Wire.endTransmission();

	Wire.beginTransmission(_address);
	Wire.write(0x00); // posición de comandos
	Wire.write(newAddress); // Dirección
	Wire.endTransmission();
}

int SRF08::getDistance(int command){

	int distance = 0, highByte, lowByte; 
  
	Wire.beginTransmission(_address);             // Start communticating with SRF08
	Wire.write(0x00);                             // Send Command Byte
	Wire.write(command);                                // Send 0x51 to start a ranging
	Wire.endTransmission();
  
	delay(100);                                     // Wait for ranging to be complete
  
	Wire.beginTransmission(_address);             // start communicating with SRFmodule
	Wire.write(0x02);                           // Call the register for start of ranging data
	Wire.endTransmission();
  
	Wire.requestFrom(_address, 2);                // Request 2 bytes from SRF module
	if(Wire.available() == 2)                    // Wait for data to arrive
	{
		highByte = Wire.read();                      // Get high byte
		lowByte = Wire.read();                       // Get low byte

		distance = (highByte << 8) + lowByte;              // Put them together
  
		return(distance);
	}
	else
		return -1;
}