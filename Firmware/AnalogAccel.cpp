#include <avr/io.h>
#include <avr/interrupt.h>
#include "AnalogAccel.h"

ISR(ANALOG_COMP_vect) //To be executed once analog compare is completed
{
	//Do stuff...
}
