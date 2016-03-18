#pragma once
#include <Arduino.h>
#include "Adafruit_TinyFlash/Adafruit_TinyFlash.h"

#ifndef CHIP_BYTES
#define CHIP_BYTES 1024UL * 1024UL
#endif
#ifndef PAGE_SIZE
#define PAGE_SIZE 256
#endif


class Memory
{
	public:
		Memory();
		~Memory();
		bool wipe();
		bool wipeSector(uint32_t addr); //Wipes 4K sector
		bool read(uint32_t addr, uint8_t* buf, uint16_t len);
		bool write(uint32_t addr, uint8_t* buf); //Writes 256 bytes
		
	private:
		Adafruit_TinyFlash chip_;
};
