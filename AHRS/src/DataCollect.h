#pragma once
#include <Arduino.h>
#include <EEPROM.h>
#include "../lib/Memory.h"
#include "../lib/ADXL377.h"

//EEPROM address where current page position is stored
#ifndef EEPROM_POS_ADDR
#define EEPROM_POS_ADDR 0x0000
#endif

class DataCollect
{
	public:
		DataCollect(Memory* mem, uint32_t addrBegin, uint8_t* memBuf);
		~DataCollect();
		uint32_t getAddress();
		void setAddress(uint32_t addr);
		void collectPage();
		void savePosition();

		// Bitmask defining which sensors were updated
		// in a given datum, as well as identifying page boundaries.
		static const uint8_t hasTimestamp = 0x01;
		static const uint8_t hasAnalogAccel = 0x02;
		static const uint8_t hasDigitalAccel = 0x04;
		static const uint8_t hasGyroscope = 0x08;
		static const uint8_t hasPressureAltitude = 0x10;
		static const uint8_t hasMagnetometer = 0x20;
		static const uint8_t isPageBegin = 0x40;
		static const uint8_t isPageEnd = 0x80;

	private:
		Memory* memory_;
		ADXL377 analogAccel_;
		uint32_t address_;
		uint8_t* memoryBuffer_;
};
