#include "DataCollect.h"

DataCollect::DataCollect(Memory* mem, uint32_t addrBegin, uint8_t* memBuf)
	: memory_(mem), address_(addrBegin), memoryBuffer_(memBuf)
{
}

DataCollect::~DataCollect()
{
	// DON'T free the memory pointer. We need it in the main loop.
}

uint32_t DataCollect::getAddress()
{
	return address_;
}

void DataCollect::setAddress(uint32_t addr)
{
	address_ = addr;
}

// Collects a page's (256 bytes) worth of data. Some data types are 
// collected more often; see implementation for details.
// The page is written in the external memory upon completion.
void DataCollect::collectPage()
{
	uint8_t i = 0;
	memoryBuffer_[i] = hasTimestamp | hasAnalogAccel | isPageBegin;
	i++; // i = 1
	*reinterpret_cast<uint32_t*>(memoryBuffer_ + i) = micros();
	i += 4; // i = 5
	*reinterpret_cast<uint16_t*>(memoryBuffer_ + i) = analogAccel_.readX();
	i += 2; // i = 7
	*reinterpret_cast<uint16_t*>(memoryBuffer_ + i) = analogAccel_.readY();
	i += 2; // i = 9
	*reinterpret_cast<uint16_t*>(memoryBuffer_ + i) = analogAccel_.readZ();
	i += 2; // i = 11
	

	memory_->write(address_, memoryBuffer_);
	address_ += PAGE_SIZE;
}

// Saves our current position (page address) into EEPROM.
// This allows the SEND state to know how many pages to send,
// even if the device reboots upon connecting the FTDI adapter
// or if power loss occurs during a violent impact.
void DataCollect::savePosition()
{
	// Only write EEPROM for pages divisible by 4.
	// This helps prolong the EEPROM lifespan.
	if(!(address_ & (3 << 8)))
		EEPROM.put(EEPROM_POS_ADDR, address_);
}
