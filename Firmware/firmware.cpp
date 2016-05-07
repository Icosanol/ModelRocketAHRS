#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRB |= _BV(DDB5);

	while(true)
	{
		PORTB |= _BV(PORTB5); //LED on
		_delay_ms(500);
		PORTB &= ~_BV(PORTB5); //LED off
 		_delay_ms(500);
	}
}
