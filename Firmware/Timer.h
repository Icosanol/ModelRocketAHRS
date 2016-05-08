#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>

class Timer
{
	public:
		Timer(uint16_t frequency);
		~Timer();
		static uint16_t getFrequency();
		uint32_t getCount() const;
	private:
		static uint16_t frequency_;
};
