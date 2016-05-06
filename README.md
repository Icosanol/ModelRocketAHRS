ModelRocketAHRS
===============
An Arduino project to measure acceleration and pressure altitude on small model rockets.

Description
-----------
This project contains two programs: One is an AVR executable designed to be installed on a board with a particular hardware configuration (see the relevant section below). The other is a serial communication utility that allows sending commands to the device or the reading and parsing of the data contained therein (only the csv format is currently supported). The entire project is licensed under the permissive [New BSD License](./LICENSE), and all recommended hardware is easily available.

Software
--------
### Arduino firmware
The board's firmware was written in pure AVR C++ instead of using the Arduino libraries. This allows the use of interrupts to communicate to hardware devices instead of using Arduino's default SPI/I2C libraries, saving precious clock cycles and allowing faster measurement frequencies, as well as reducing analog measurement noise by sleeping the processor during measurement. Compilation and installation on most Unices should be as simple as:

```bash
make install
```

which will compile the binary and attempt to install it on the AVR through a serial port. If your FTDI or other serial device is not the same as the one referenced in the makefile, you will need to specify it by setting the variable used by the Makefile:

```bash
make install PORT=/dev/ttyS1
```

Of course, you will need a compiler, linker, and uploader for the AVR architecture:

```bash
sudo apt-get install avrdude avrdude-doc avr-libc binutils-avr gcc-avr gcc-avr gdb-avr # Debian-based distros
sudo yum install avr* # Fedora-based distros
```

Windows users could use [WinAVR](https://sourceforge.net/projects/winavr/), but I have never tried this, so it might actually be simpler to launch a Linux virtual machine and connect your USB-to-serial device to the VM.

Mac OS X is awesome, as it comes with some of the standard GNU tools, including make (though you must install XCode). The AVR tools [can be installed with Homebrew](http://maxembedded.com/2015/06/setting-up-avr-gcc-toolchain-on-linux-and-mac-os-x/), and then the UNIX compilation steps can be followed as if you were on Linux.

Hardware
--------
### Board and sensors
The following hardware is required for the Arduino portion of the project. Links are provided to [Adafruit](https://www.adafruit.com/) as an example only, as this is where the components were purchased for the original version of this project. This does not constitute an endorsment of Adafruit Industries. Most of the components can likely be substituted for various alternatives depending on availability, with slight modifications to the source code.

* [Winbond W25Q80BV 1 MByte SPI Flash (1564)](https://www.adafruit.com/product/1564)  
  This is the flash memory used for saving flight data. **It is discontinued.** Similar chips by the same manufacturer could still be used by changing only a few lines according to the datasheet. Alternatively, the memory interface could be rewritten to accomodate other sources of cheap SPI flash memory, such as MicroSD cards (Bonus: more storage space).

* [Adafruit 10-DOF IMU Breakout](https://www.adafruit.com/product/1604)   
  This breakout board is actually three different sensors on one circuit:   

  1. The L3GD20H is a 3-axis gyroscope allowing for measurement of the rate at which the rocket spins on its vertical axis or tumbles on its pitch and roll axes.
  2. The LSM303 combines a 3-axis compass to determine orientation relative to the fixed magnetic field of the Earth, and a factory-calibrated accelerometer for precise measurement of smaller accelerations (±16g).
  3. The BMP180 pressure sensor allows measurement of static pressure, precise estimation of pressure altitude, as well as air temperature (the last one may not be important on a model rocket, but may be useful for longer flights on, say, makeshift weather balloons).

  All three chips are on the I2C bus, and therefore use only two pins in total on the microcontroller.

### Assembly
The flexibility of AVR microcontrollers' GPIO interface means that there are lots of valid ways of connecting all components.

Credits
-------
Special thanks to [Adafruit](https://www.adafruit.com/) for their amazing tutorials on the various quirks of embeddded programming.

[Qt](https://www.qt.io/) is magic. It makes serial interface programming probably 1000x easier than writing kernel drivers. Also, it allows the exact same source code to run on nearly all operating systems, which is actually impressive for native GUI applications that communicate with low-level hardware. Please use it.
