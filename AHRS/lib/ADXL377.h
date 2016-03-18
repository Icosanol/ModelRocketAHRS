#pragma once
#include <Arduino.h>

#define Xpin 

class ADXL377
{
	public:
		ADXL377();
		~ADXL377();
		uint16_t readX();
		uint16_t readY();
		uint16_t readZ();

	private:
		static const int pinX = A0;
		static const int pinY = A1;
		static const int pinZ = A2;
};
