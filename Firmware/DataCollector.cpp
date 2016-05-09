#include "DataCollector.h"

DataCollector::DataCollector(AnalogAccel& accel, Timer& timer)
	:accel_(accel), timer_(timer)
{
	updateTimestamp();
}

DataCollector::~DataCollector()
{
}

void DataCollector::collectPage()
{
	writeTimestamp(page_);

	uint16_t i;

	for(i = sizeof(timestamp_); i <= (PAGELEN - 6); i += 6)
	{
		while(timer_.getCount() == timestamp_); //Wait for next tick
		updateTimestamp();
		writeAnalogAccel(page_ + i);
	}
}

const uint8_t* DataCollector::getPagePtr() const
{
	return page_;
}

void DataCollector::updateTimestamp()
{
	timestamp_ = timer_.getCount();
}

void DataCollector::writeTimestamp(uint8_t* out)
{
	out[0] = (timestamp_ >> 24);
	out[1] = (timestamp_ >> 16);
	out[2] = (timestamp_ >> 8);
	out[3] = (timestamp_ & 0xFF);
}

void DataCollector::writeAnalogAccel(uint8_t* out)
{
	uint16_t x = accel_.getX();
	uint16_t y = accel_.getY();
	uint16_t z = accel_.getZ();
	out[4] = (x >> 8);
	out[5] = (x & 0xFF);
	out[6] = (y >> 8);
	out[7] = (y & 0xFF);
	out[8] = (z >> 8);
	out[9] = (z & 0xFF);
}
