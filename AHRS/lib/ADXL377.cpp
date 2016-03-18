#include "ADXL377.h"

ADXL377::ADXL377()
{
}

ADXL377::~ADXL377()
{
}

uint16_t ADXL377::readX()
{
	return analogRead(pinX);
}

uint16_t ADXL377::readY()
{
	return analogRead(pinY);
}

uint16_t ADXL377::readZ()
{
	return analogRead(pinZ);
}

