#include "src/DataCollect.h"
#include "lib/Memory.h"

Memory memory;
uint32_t endAddress;
uint8_t memoryBuffer[PAGE_SIZE];
uint8_t sensorBuffer[PAGE_SIZE];

DataCollect dataCollect(&memory, 0UL, sensorBuffer, memoryBuffer);
enum State {WAIT, COLLECT, SEND, ERASE} state = WAIT;

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	switch(state)
	{
		case WAIT:
			// Do nothing, wait to be forced out by interrupt
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
			state = WAIT;
			break;
	}
}
