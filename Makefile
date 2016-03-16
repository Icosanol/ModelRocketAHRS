.PHONY: all clean upload
LIB_DIR = ./lib
SRC_DIR = ./src
BIN_DIR = ./bin
MAIN_SRC_FILE = ModelRocketAHRS.ino

ARDUINO_DIR = ~/Programs/arduino-1.6.8
ARDUINO = $(ARDUINO_DIR)/arduino
ARDUINO_FLAGS = --pref build.path=$(BIN_DIR) --preserve-temp-files

VENDOR = adafruit
ARCHITECTURE = avr
BOARD_NAME = protrinket3ftdi
BOARD = $(VENDOR):$(ARCHITECTURE):$(BOARD_NAME)

all: clean
	@mkdir -p $(BIN_DIR)
	$(ARDUINO) --verify $(ARDUINO_FLAGS) $(MAIN_SRC_FILE)
upload: clean
	@mkdir -p $(BIN_DIR)
	$(ARDUINO) --upload $(ARDUINO_FLAGS) $(MAIN_SRC_FILE)
clean:
	rm -rf bin
