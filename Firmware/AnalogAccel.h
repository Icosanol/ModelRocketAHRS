#pragma once
#include "Geometry.h"

class AnalogAccel
{
	public:
		AnalogAccel();
		~AnalogAccel();
	private:
		static volatile Axis& currentAxis_;
};
