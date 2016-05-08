#include "Timer.h"

volatile uint32_t count;
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
	OCR1A = (F_CPU / frequency_ / 2 / 8) - 1; //Formula in datasheet
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
	return count;
}
