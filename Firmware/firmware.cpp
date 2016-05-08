#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "AnalogAccel.h"

int main()
{
	sei();

	AnalogAccel analogAccel;
	DDRB |= _BV(DDB5);

	while(true)
	{
		if(analogAccel.getZ() > 512)
			PORTB |= _BV(PORTB5);
		else
			PORTB &= ~_BV(PORTB5);
	}
}
