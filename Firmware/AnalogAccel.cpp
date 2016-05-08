#include "AnalogAccel.h"

volatile uint16_t rawAnalogData[3] = {0, 0, 0};
volatile AnalogAxis currentAxis = X;

ISR(ADC_vect) //To be executed once analog compare is completed
{
	ADMUX = (ADMUX & 0xF0) | nextAxis(currentAxis); //Next conversion
	rawAnalogData[prevAxis(currentAxis)] = ADC; //Read *last* conversion
	currentAxis = nextAxis(currentAxis);
}

AnalogAccel::AnalogAccel()
{
	DDRC &= ~_BV(DDC0) & ~_BV(DDC1) & ~_BV(DDC2); //Pins as inputs

	//Prescaler of 128 (12MHz / 128 == 93.75 kHz),
	//recommended value is 50-200kHz. Also: Enable interrupt,
	//enable auto-triggering, start conversion and turn the ADC on.
	ADCSRA |= _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2) | _BV(ADIE) \
		| _BV(ADATE) | _BV(ADSC) | _BV(ADEN);

	ADCSRB = 0x00; //Free-running mode
	
	ADMUX = _BV(REFS0) | currentAxis; //Set channel to current axis.

	//Disable digital input buffers for those pins (saves power)
	DIDR0 |= _BV(ADC0D) | _BV(ADC1D) | _BV(ADC2D);
}

AnalogAccel::~AnalogAccel()
{
	ADCSRA &= ~_BV(ADEN); //Disable the ADC (also disables the interrupt)
}

uint16_t AnalogAccel::getX() const
{
	uint16_t dataX = 0;

	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		//Atomic read of 16-bit value necessary on 8-bit CPU
		dataX = rawAnalogData[X];
	}

	return dataX;
}

uint16_t AnalogAccel::getY() const
{
	uint16_t dataY = 0;

	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		dataY = rawAnalogData[Y];
	}

	return dataY;
}

uint16_t AnalogAccel::getZ() const
{
	uint16_t dataZ = 0;

	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		dataZ = rawAnalogData[Z];
	}

	return dataZ;
}

AnalogAxis nextAxis(AnalogAxis axis)
{
	switch(axis)
	{
		case X:
			return Y;
		case Y:
			return Z;
		case Z:
			return X;
		default:
			return X;
	};
}

AnalogAxis prevAxis(AnalogAxis axis)
{
	switch(axis)
	{
		case X:
			return Z;
		case Y:
			return X;
		case Z:
			return Y;
		default:
			return X;
	};
}
