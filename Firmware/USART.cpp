// Copyright (c) 2015-2016 Marc-Andre Servant. All rights reserved.
// Licenced under the New BSD Licence (see included file)

#include "USART.h"

uint32_t USART::baudrate_ = 0;

USART::USART(uint32_t baudrate)
{
	baudrate_ = baudrate;
	UBRR0 = (F_CPU / 8 / baudrate_) - 1;
	UCSR0A |= _BV(U2X0); //Double baud rate
	UCSR0B |= _BV(RXEN0) | _BV(TXEN0); //Rx and Tx enabled (full-duplex)
	UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00); //8-bit, no parity, 1 stop bit
}

USART::~USART()
{
	UCSR0B = 0; //Disable Tx and Rx
}

uint32_t USART::getBaudRate()
{
	return baudrate_;
}

bool USART::hasRxData() const
{
	return (UCSR0A & _BV(RXC0)) != 0; //Rx complete flag
}

void USART::read(uint8_t* out, uint16_t length) const
{
	for(uint16_t i = 0; i < length; i++)
	{
		while(!(UCSR0A & _BV(RXC0))); //Wait till byte ready
		out[i] = UDR0;
	}
}

uint8_t USART::readbyte() const
{
	uint8_t data;
	read(&data, sizeof(data));
	return data;
}

void USART::write(const uint8_t* in, uint16_t length) const
{
	for(uint16_t i = 0; i < length; i++)
	{
		while(!(UCSR0A & _BV(UDRE0))); //Wait till prevoius byte sent
		UDR0 = in[i];
	}
}

void USART::writebyte(uint8_t data) const
{
	write(&data, sizeof(data));
}
