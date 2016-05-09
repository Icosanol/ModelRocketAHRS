#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "AnalogAccel.h"
#include "Timer.h"
#include "USART.h"
#include "Memory.h"
#include "DataCollector.h"

enum State {WAIT, ERASE, COLLECT, DUMP};

void readState(USART& usart, State& state)
{
	if(!usart.hasRxData())
		return;

	uint8_t cmd = usart.readbyte();

	switch(cmd)
	{
		case 'W':
			state = WAIT;
			break;
		case 'E':
			state = ERASE;
			break;
		case 'C':
			state = COLLECT;
			break;
		case 'D':
			state = DUMP;
			break;
	};
}

int main()
{
	sei();

	AnalogAccel analogAccel;
	Timer timer(1000); //1000Hz count frequency
	USART usart(57600); //Give or take 0.2% rounding error
	Memory memory(&PORTB, PORTB2, timer);
	DataCollector dataCollector(analogAccel, timer);

	State currentState = WAIT;

	while(true)
	{
		switch(currentState)
		{
			case WAIT: //Just loop until USART switches state
				break;
			case ERASE:
				break;
			case COLLECT:
				break;
			case DUMP:
				break;
		};
	}

	return 0;
}
