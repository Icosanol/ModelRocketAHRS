#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "AnalogAccel.h"

volatile Axis currentAxis = X;

ISR(ANALOG_COMP_vect) //To be executed once analog compare is completed
{
	//Do stuff...
}

AnalogAccel::AnalogAccel()
{
	//Prescaler of 64 (12MHz / 64 == 187.5 kHz),
	//recommended value is 50-200kHz. Also: Enable interrupt,
	//enable auto-triggering, start conversion and turn the ADC on.
	ADCSRA |= _BV(ADPS1) | _BV(ADPS2) | _BV(ADIE) \
		| _BV(ADSC) | _BV(ADEN);

	//Disable digital input buffers for those pins (saves power)
	DIDR0 |= _BV(ADC0D) | _BV(ADC1D) | _BV(ADC2D);
}

AnalogAccel::~AnalogAccel()
{
	ADCSRA &= ~_BV(ADEN); //Disable the ADC (also disables the interrupt)
}

Axis AnalogAccel::getCurrentAxis()
{
	return currentAxis_;
}

//Allows iterating through all 3 axes, measuring one at a time.
void AnalogAccel::nextAxis()
{
	switch(getCurrentAxis())
	{
		case X:
			currentAxis_ = Y;
			break;
		case Y:
			currentAxis_ = Z;
			break;
		case Z:
			currentAxis_ = X;
			break;
	};
}

volatile Axis& AnalogAccel::currentAxis_ = currentAxis;
