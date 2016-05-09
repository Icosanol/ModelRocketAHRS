#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "AnalogAccel.h"
#include "Timer.h"
#include "USART.h"
#include "Memory.h"

int main()
{
	sei();

	AnalogAccel analogAccel;
	Timer timer(1000); //1000Hz count frequency
	USART usart(57600); //Give or take 0.2% rounding error
	Memory memory(&PORTB, PORTB2, timer);

	DDRB |= _BV(DDB5);

	memory.eraseChip();

	char sent[] = "The quick brown fox jumps over the lazy dog.\r\n";
	memory.writePage((uint8_t*)sent, 0);
	timer.wait(10);
	uint8_t recv[sizeof(sent)];
	memory.read(recv, 0, sizeof(recv));

	usart.write(recv, sizeof(recv));

	return 0;
}
