#include "DataCollector.h"

DataCollector::DataCollector(AnalogAccel& accel, Timer& timer)
	:accel_(accel), timer_(timer), timestamp_(0)
{
}

DataCollector::~DataCollector()
{
}

void DataCollector::CollectPage()
{
	uint8_t i;

	for( i = 0; i <= (PAGELEN - 10); i += 10)
	{
		while(timer_.getCount() == timestamp_); //Wait for next tick
		measureAccel(page_ + i);
	}

	page_[i++] = 'V';
	page_[i++] = 'a';
	page_[i++] = 'l';
	page_[i++] = 'i';
	page_[i++] = 'd';
	page_[i] = '\0';
}

const uint8_t* DataCollector::getPagePtr() const
{
	return page_;
}

void DataCollector::measureAccel(uint8_t* out)
{
	timestamp_ = timer_.getCount();
	out[0] = (timestamp_ >> 24);
	out[1] = (timestamp_ >> 16);
	out[2] = (timestamp_ >> 8);
	out[3] = (timestamp_ & 0xFF);

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
