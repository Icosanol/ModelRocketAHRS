#pragma once
#include "Geometry.h"

class AnalogAccel
{
	public:
		AnalogAccel();
		~AnalogAccel();
		static Axis getCurrentAxis();
		static void nextAxis();
	private:
		static volatile Axis& currentAxis_;
};
