#pragma once
#include <avr/io.h>

class USART
{
	public:
		USART(uint32_t baudrate);
		~USART();
		static uint32_t getBaudRate();
		bool hasRxData() const;
		void read(uint8_t* out, uint8_t length) const;
		uint8_t readbyte() const;
		void write(const uint8_t* in, uint8_t length) const;
		void writebyte(uint8_t data) const;
	private:
		static uint32_t baudrate_;
};
