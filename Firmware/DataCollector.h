#pragma once
#include "AnalogAccel.h"
#include "Timer.h"
#include "Memory.h"

class DataCollector
{
	public:
		DataCollector(AnalogAccel& accel, Timer& timer);
		~DataCollector();
		void collectPage();
		const uint8_t* getPagePtr() const;
	private:
		void measureAccel(uint8_t* out);
		AnalogAccel& accel_;
		Timer& timer_;
		uint8_t page_[PAGELEN];
		uint32_t timestamp_;
};
