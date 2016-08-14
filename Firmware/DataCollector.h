// Copyright (c) 2015-2016 Marc-Andre Servant. All rights reserved.
// Licenced under the New BSD Licence (see included file)

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
		void updateTimestamp();
		void writeTimestamp(uint8_t* out);
		void writeAnalogAccel(uint8_t* out);
		AnalogAccel& accel_;
		Timer& timer_;
		uint8_t page_[PAGELEN];
		uint32_t timestamp_;
};
