// Copyright (c) 2015-2016 Marc-Andre Servant. All rights reserved.
// Licenced under the New BSD Licence (see included file)

#include "Timer.h"

volatile uint32_t count; //At 1kHz, this will take over a month to overflow
uint16_t Timer::frequency_;

ISR(TIMER1_COMPA_vect)
{
	count++;
}

Timer::Timer(uint16_t frequency)
{
	count = 0;
	frequency_ = frequency;

	TCCR1B |= _BV(CS11) | _BV(WGM12); //CTC mode, prescaler of 8
	OCR1A = (F_CPU / frequency_ / 8) - 1; //Formula in datasheet
	TIMSK1 |= _BV(OCIE1A); //Enable interrupt on compare match
}

Timer::~Timer()
{
	TIMSK1 &= ~_BV(OCIE1A); //Disabling interrupt stops counting
	count = 0;
}

uint16_t Timer::getFrequency()
{
	return frequency_;
}

uint32_t Timer::getCount() const
{
	uint32_t buffer = 0;
	
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		buffer = count;
	}

	return buffer;
}

void Timer::wait(uint32_t ticks) const
{
	uint32_t startCount = getCount();

	while (getCount() < startCount + ticks);
}
