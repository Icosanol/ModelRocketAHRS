#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "AnalogAccel.h"
#include "Timer.h"

int main()
{
	sei();

	AnalogAccel analogAccel;
	Timer timer(1000); //Count increases 1000x per second (every 1 ms)

	DDRB |= _BV(DDB5);

	while(true)
	{
		if((timer.getCount() < 10000) != (analogAccel.getZ() > 512))
			PORTB |= _BV(PORTB5);
		else
			PORTB &= ~_BV(PORTB5);
	}
}
