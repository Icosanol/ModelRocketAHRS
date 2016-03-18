#include "src/DataCollect.h"
#include "lib/Memory.h"
#include <avr/io.h>

Memory memory;
uint32_t endAddress;
uint8_t memoryBuffer[PAGE_SIZE];

DataCollect dataCollect(&memory, 0UL, memoryBuffer);
enum State {WAIT, COLLECT, SEND, ERASE} state = WAIT;

void setup()
{
	Serial.begin(57600);
	delay(4000);
	Serial.println(F("R: Ready! Please enter desired option:"));
}

void loop()
{
	switch(state)
	{
		case WAIT:
			break;

		case COLLECT:
			if(endAddress != 0)
				break; //Chip must be erased prior to flight
			
			dataCollect.collectPage();
			dataCollect.savePosition();
			break;

		case SEND:
			// Position next to the last page written by COLLECT
			EEPROM.get(EEPROM_POS_ADDR, endAddress);
			// We write the number of bytes the client should get.
			Serial.write(reinterpret_cast<uint8_t*>(&endAddress), 
				sizeof(endAddress));

			for(uint32_t i = 0UL; i < endAddress; i += PAGE_SIZE)
			{
				memory.read(i, memoryBuffer, PAGE_SIZE);
				Serial.write(memoryBuffer, PAGE_SIZE);
			}
			
			//The user probably does not want his data sent twice.
			state = WAIT;
			break;

		case ERASE:
			//Boom. Ka-Pow. Whoosh. Everything. Gone.
			memory.wipe();
			endAddress = 0UL;
			dataCollect.setAddress(0UL);
			dataCollect.savePosition(); //Start back at zero
			Serial.println(F("E: Erase complete."));
			state = WAIT;
			break;
	}

	if(Serial.available())
	{
		uint8_t data = Serial.read();
		
		switch(data)
		{
			case 'W':
				state = WAIT;
				break;
			case 'C':
				state = COLLECT;
				break;
			case 'S':
				state = SEND;
				break;
			case 'E':
				state = ERASE;
				break;
			default:
				state = WAIT;
				break;
		}
	}
}
