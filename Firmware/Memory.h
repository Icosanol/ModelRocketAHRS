#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "Timer.h"

#define PAGELEN 256
#define NPAGES 4096 //That's 256 * 4096 = 1 048 576 bytes, or 1 MiB

class Memory
{
	public:
		Memory(Timer& timer);
		~Memory();
	private:
		Timer& timer_;
};
