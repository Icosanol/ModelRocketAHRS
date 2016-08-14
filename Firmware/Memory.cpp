// Copyright (c) 2015-2016 Marc-Andre Servant. All rights reserved.
// Licenced under the New BSD Licence (see included file)

#include "Memory.h"

volatile uint8_t pageBuffer[PAGELEN];
volatile uint16_t index = 0;
volatile uint8_t* port = 0;
uint8_t pin = 0;

ISR(SPI_STC_vect) //Executed when SPI transfer is complete
{
	if(index < PAGELEN)
	{
		SPDR = pageBuffer[index];
		index++;
	}
	else //Chip ignores data if we overflowed
	{	
		SPCR &= ~_BV(SPIE); //Disables its own interrupt
		index = 0;
		*port |= (1 << pin); //Deselect chip. Write enable bit clears by itself.
	}
}

Memory::Memory(volatile uint8_t* cs_port, uint8_t cs_pin, Timer& timer)
	:cs_port_(cs_port), cs_pin_(cs_pin), timer_(timer)
{
	deselect();
	port = cs_port_;
	pin = cs_pin_;
	*(cs_port_ - 1) |= (1 << cs_pin_); //&PORTn - 1 == &DDRn
	DDRB |= _BV(DDB3) | _BV(DDB5); //MOSI, SCK as outputs
	DDRB &= ~_BV(DDB4); //MISO as input

	//Start SPI in Master mode, clock prescaler is 16.
	SPCR |= _BV(MSTR) | _BV(SPE) | _BV(SPR0);
	SPSR |= _BV(SPI2X); //Double the SCK frequency (that's F_CPU / 8)
}

Memory::~Memory()
{
	SPCR &= ~_BV(SPE); //Clear the enable bit in control register
}

bool Memory::read(uint8_t* out, uint32_t addr, uint16_t len)
{
	if(!beginRead(addr))
		return false;

	for(uint16_t i = 0; i < len; i++)
		out[i] = transferbyte();

	deselect();
	return true;
}

bool Memory::writePage(const uint8_t* in, uint32_t addr)
{
	if(addr >= PAGELEN * NPAGES || !isReady() || !writeEnable())
		return false;

	for(uint16_t i = 0; i < PAGELEN; i++)
		pageBuffer[i] = in[i];

	index = 0;
	sendCmd(PAGE_WRITE);
	transferbyte(addr >> 16); //Otherwise we'll have endianness problems
	transferbyte(addr >> 8);
	SPDR = 0; //LSB of address is ignored, so it's faster to just zero it.
	SPCR |= _BV(SPIE);

	//At that point, the interrupt will transmit one byte at a time.

	return true;
}

bool Memory::eraseChip()
{
	if(!isReady() || !writeEnable())
		return false;

	sendCmd(CHIP_ERASE);
	deselect();

	//Erase takes ~5s, we wait double that to be sure
	timer_.wait(10 * timer_.getFrequency());

	return true;
}

void Memory::sendCmd(Command cmd)
{
	select();
	transferbyte(cmd);
}

bool Memory::isReady()
{
	sendCmd(READ_STATUS_REG_1);
	uint8_t response = transferbyte();
	deselect();

	return (response & (1 << BUSY_BIT)) == 0;
}

bool Memory::beginRead(uint32_t address)
{
	if(address >= PAGELEN * NPAGES || !isReady())
		return false;

	sendCmd(READ);
	transferbyte(address >> 16);
	transferbyte(address >> 8);
	transferbyte(address & 0xFF);

	return true;
}

bool Memory::writeEnable()
{
	sendCmd(WRITE_ENABLE);
	deselect();
	
	sendCmd(READ_STATUS_REG_1);
	uint8_t response = transferbyte();
	deselect();

	return (response & (1 << WRITE_EN_BIT)) != 0;
}

void Memory::writeDisable()
{
	sendCmd(WRITE_DISABLE);
	deselect();
}

uint8_t Memory::transferbyte(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & _BV(SPIF))); //Wait for transfer complete
	return SPDR; //Response sent in same register
}

void Memory::select()
{
	*cs_port_ &= ~(1 << cs_pin_);
}

void Memory::deselect()
{
	*cs_port_ |= (1 << cs_pin_);
}
