#include "Memory.h"

Memory::Memory()
	:chip_()
{
	chip_.begin();
}

Memory::~Memory()
{
}

// WARNING: Deletes all data (Ka-BOOM)
bool Memory::wipe()
{
	return chip_.eraseChip();
}

bool Memory::wipeSector(uint32_t addr)
{
	return chip_.eraseSector(addr);
}

bool Memory::read(uint32_t addr, uint8_t* buf, uint16_t len)
{
	bool isReady = chip_.beginRead(addr);
	
	if(!isReady) //Problem with chip, read error
		return false;

	for(uint16_t i = 0; i < len; i++)
		buf[i] = chip_.readNextByte();
	
	chip_.endRead();

	return true;
}

// Due to a hardware limitation, one-step writes MUST be done
// on 256-byte pages, and they MUST align to a 256-byte boundary.
// Also, the sector the page resides in must be erased before
// a write can be performed. This is true of any flash device.
// See wipe functions above.
bool Memory::write(uint32_t addr, uint8_t* buf)
{
	return chip_.writePage(addr, buf);
}
