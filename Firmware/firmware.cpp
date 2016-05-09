#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "AnalogAccel.h"
#include "Timer.h"
#include "USART.h"

int main()
{
	sei();

	AnalogAccel analogAccel;
	Timer timer(1000); //1000Hz count frequency
	USART usart(57600); //Give or take 0.2% rounding error

	DDRB |= _BV(DDB5);

	while(true)
	{
		usart.writebyte(usart.readbyte());
	}
}
