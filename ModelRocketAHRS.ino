#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lib/Adafruit_TinyFlash/Adafruit_TinyFlash.h"

int main()
{
	DDRB |= _BV(DDB5);
	
	Adafruit_TinyFlash memory;

	for(;;)
	{
		_delay_ms(50); //Blink! Blink!
		PORTB |= _BV(PORTB5);
		_delay_ms(50);
		PORTB &= ~_BV(PORTB5);
	}
}
