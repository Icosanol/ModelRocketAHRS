#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

enum AnalogAxis {X, Y, Z};

AnalogAxis nextAxis(AnalogAxis axis);
AnalogAxis prevAxis(AnalogAxis axis);

class AnalogAccel
{
	public:
		AnalogAccel();
		~AnalogAccel();
		uint16_t getX() const;
		uint16_t getY() const;
		uint16_t getZ() const;
};
