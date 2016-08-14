// Copyright (c) 2015-2016 Marc-Andre Servant. All rights reserved.
// Licenced under the New BSD Licence (see included file)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "AnalogAccel.h"
#include "Timer.h"
#include "USART.h"
#include "Memory.h"
#include "DataCollector.h"

#define R_BUF_SZ 64

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
	uint32_t address = 0;
	DataCollector dataCollector(analogAccel, timer);

	State currentState = WAIT;

	char eraseSuccess[] = "Chip erased\n";
	char eraseFail[] = "Erase failed\n";

	while(true)
	{
		switch(currentState)
		{
			case WAIT: //Just loop until USART switches state
				break;
			case ERASE:
				address = 0;
				if(memory.eraseChip())
					usart.write((uint8_t*)eraseSuccess,
						sizeof(eraseSuccess));
				else
					usart.write((uint8_t*)eraseFail, 
						sizeof(eraseFail));

				currentState = WAIT;
				break;
			case COLLECT:
				dataCollector.collectPage();
				if(memory.writePage(dataCollector.getPagePtr(), address))
					address += PAGELEN;
				else //Memory full or not responsive
					currentState = WAIT;
				break;
			case DUMP:
				for(uint32_t readAddr = 0;
					readAddr <= (PAGELEN * NPAGES - R_BUF_SZ);
					readAddr += R_BUF_SZ)
				{
					uint8_t buf[R_BUF_SZ];
					memory.read(buf, readAddr, R_BUF_SZ);
					usart.write(buf, R_BUF_SZ);
				}

				currentState = WAIT;
				break;
		};

		readState(usart, currentState);
	}

	return 0;
}
