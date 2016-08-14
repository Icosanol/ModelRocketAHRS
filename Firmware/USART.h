// Copyright (c) 2015-2016 Marc-Andre Servant. All rights reserved.
// Licenced under the New BSD Licence (see included file)

#pragma once
#include <avr/io.h>

class USART
{
	public:
		USART(uint32_t baudrate);
		~USART();
		static uint32_t getBaudRate();
		bool hasRxData() const;
		void read(uint8_t* out, uint16_t length) const;
		uint8_t readbyte() const;
		void write(const uint8_t* in, uint16_t length) const;
		void writebyte(uint8_t data) const;
	private:
		static uint32_t baudrate_;
};
