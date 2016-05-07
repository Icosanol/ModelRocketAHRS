#include <avr/io.h>
#include <avr/interrupt.h>
#include "AnalogAccel.h"

volatile Axis currentAxis = X;

ISR(ANALOG_COMP_vect) //To be executed once analog compare is completed
{
	//Do stuff...
}

AnalogAccel::AnalogAccel()
{
}

AnalogAccel::~AnalogAccel()
{
}

volatile Axis& AnalogAccel::currentAxis_ = currentAxis;
