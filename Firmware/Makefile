# Location where output files will be stored
BUILD=./build

# Location of the built executable
EXEC=$(BUILD)/firmware
HEXFILE=$(EXEC).hex

# Compiler-generated dependency lists
DEPENDENCIES=$(wildcard $(BUILD)/*.d)
include $(DEPENCENCIES)

# Source files to compile
SRC=$(wildcard *.cpp)
OBJDEPS=$(patsubst %.cpp, $(BUILD)/%.o, $(SRC))

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
