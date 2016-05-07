# Location where output files will be stored
BUILD=./build

# Location of the built executable
EXEC=$(BUILD)/firmware
HEXFILE=$(EXEC).hex

# Name of target microcontroller, the Adafruit Pro Trinket is an Atmega238p.
MCU=atmega328p

# CPU clock speed, used for calculations within the preprocessor.
CLKSPD=12000000UL

# Port used for uploading to the board.
# Use "make install PORT=/dev/somewhere" if not the same on your system.
PORT?=/dev/ttyS0

# Compiler-generated dependency lists
DEPENDENCIES=$(wildcard $(BUILD)/*.d)

# Compilation options:
CXX=avr-gcc
CXXFLAGS=-g -O3 -mmcu=$(MCU) -MMD -DF_CPU=$(CLKSPD) -std=c++11\
	-Wall -Wextra -Werror -pedantic-errors

CONVERT=avr-objcopy
CONVERTFLAGS=-g -O ihex -R .eeprom

.PHONY: all install clean

all: $(EXEC)

install: $(HEXFILE)

$(EXEC): $(OBJDEPS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJDEPS)

$(HEXFILE): $(EXEC)
	$(CONVERT) $(CONVERTFLAGS) $(EXEC) $(HEXFILE)
