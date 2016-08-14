// Copyright (c) 2015-2016 Marc-Andre Servant. All rights reserved.
// Licenced under the New BSD Licence (see included file)

#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

class Timer
{
	public:
		Timer(uint16_t frequency);
		~Timer();
		static uint16_t getFrequency();
		uint32_t getCount() const;
		void wait(uint32_t ticks) const;
	private:
		static uint16_t frequency_;
};
