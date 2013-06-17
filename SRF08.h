#ifndef SFR08_h
#define SRF08_h

#include "Arduino.h"

class SRF08
{
	public:
		SRF08(uint8_t address);
		int getVersion();
		int getLuminosity();
		int getDistanceIn();
		int getDistanceCm();
		int getDistanceMs();
		void changeAddress(int newAddress);

	private:
		int getDistance(int command);
};

#endif