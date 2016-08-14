// Copyright (c) 2015-2016 Marc-Andre Servant. All rights reserved.
// Licenced under the New BSD Licence (see included file)

#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "Timer.h"

#define PAGELEN 256UL
#define NPAGES 4096UL //That's 256 * 4096 = 1 048 576 bytes, or 1 MiB
#define BUSY_BIT 0
#define WRITE_EN_BIT 1

enum Command
{
	PAGE_WRITE = 0x02,
	READ = 0x03,
	WRITE_ENABLE = 0x06,
	WRITE_DISABLE = 0x04,
	READ_STATUS_REG_1 = 0x05,
	CHIP_ERASE = 0x60
};

class Memory
{
	public:
		Memory(volatile uint8_t* cs_port, uint8_t cs_pin, Timer& timer);
		~Memory();
		bool read(uint8_t* out, uint32_t addr, uint16_t len);
		bool writePage(const uint8_t* in, uint32_t addr);
		bool eraseChip();
	private:
		void sendCmd(Command cmd); //Also selects chip
		bool isReady();
		bool writeEnable(); //Returns true if ready, false if chip busy
		void writeDisable();
		bool beginRead(uint32_t address);
		uint8_t transferbyte(uint8_t data = 0);
		void select();
		void deselect();

		volatile uint8_t* cs_port_;
		uint8_t cs_pin_;
		Timer& timer_;
};
