# Copyright (c) 2015-2016 Marc-Andre Servant. All rights reserved.
# Licenced under the New BSD Licence (see included file)

# Location where output files will be stored
BUILD=build

# Location of the built executable
EXEC=$(BUILD)/firmware
HEXFILE=$(EXEC).hex

# Compiler-generated dependency lists

# Source files to compile
SRC=$(wildcard *.cpp)

# We now determine the name of the compiler's output files.
OBJDEPS=$(patsubst %.cpp, $(BUILD)/%.o, $(SRC))
DEPENDENCIES=$(patsubst %.o, %.d, $(OBJDEPS))

# Name of target microcontroller, the Adafruit Pro Trinket is an Atmega238p.
MCU=atmega328p

# CPU clock speed, used for calculations within the preprocessor.
CLKSPD=12000000UL

# Port used for uploading to the board.
# Use "make install PORT=/dev/somewhere" if not the same on your system.
PORT?=/dev/ttyUSB0

# Compilation options:
CXX=avr-gcc
CXXFLAGS=-g -O3 -mmcu=$(MCU) -MMD -DF_CPU=$(CLKSPD) -std=c++11\
	-Wall -Wextra -Werror -pedantic-errors

CONVERT=avr-objcopy
CONVERTFLAGS=-g -O ihex -R .eeprom

UPLOADER=avrdude
UPLOADERFLAGS=-c arduino -p $(MCU) -P $(PORT)

.PHONY: all install clean

all: $(EXEC)

-include $(DEPENDENCIES)

install: $(HEXFILE)
	$(UPLOADER) $(UPLOADERFLAGS) -U flash:w:$<

$(BUILD)/%.o: %.cpp
	@mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(EXEC): $(OBJDEPS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(HEXFILE): $(EXEC)
	$(CONVERT) $(CONVERTFLAGS) $< $@

clean:
	rm -rf $(BUILD)
