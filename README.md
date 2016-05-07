ModelRocketAHRS
===============
An Arduino project to measure acceleration and pressure altitude on small model rockets.

Description
-----------
This project contains two programs: One is an AVR executable designed to be installed on a board with a particular hardware configuration (see the relevant section below). The other is a serial communication utility that allows sending commands to the device or the reading and parsing of the data contained therein (only the csv format is currently supported). The entire project is licensed under the permissive [New BSD License](./LICENSE), and all recommended hardware is easily available.

Software
--------
### Arduino Firmware
The board's firmware was written in pure AVR C++ instead of using the Arduino libraries. This allows the use of interrupts to communicate to hardware devices instead of using Arduino's default SPI/I2C libraries, saving precious clock cycles and allowing faster measurement frequencies, as well as reducing analog measurement noise by sleeping the processor during measurement. Compilation and installation on most Unices should be as simple as:

```bash
make install
```

which will compile the binary and attempt to install it on the AVR through a serial port. If your FTDI or other serial device is not the same as the one referenced in the makefile, you will need to specify it by setting the variable used by the Makefile:

```bash
make install PORT=/dev/SomeDevice
```

Sometimes, the serial device selected is the correct one, but avrdude will not be able to upload any data to it due to permissions issues. In that case, use

```bash
sudo chmod a+rw /dev/SomeDevice
```
to give users permission to write data to the device, replacing SomeDevice with the actual name of your USB-to-serial adapter (obtained by running `ls /dev` both before and after plugging in the adapter and seeing what got added).

Of course, you will need a compiler, linker, and uploader for the AVR architecture:

```bash
sudo apt-get install avrdude avrdude-doc avr-libc binutils-avr gcc-avr gcc-avr gdb-avr # Debian-based distros
sudo yum install avr* # Fedora-based distros
```

Windows users could use [WinAVR](https://sourceforge.net/projects/winavr/), but I have never tried this, so it might actually be simpler to launch a Linux virtual machine and connect your USB-to-serial device to the VM.

Mac OS X comes with some of the standard GNU tools, including make (though you must install Xcode). The AVR tools [can be installed with Homebrew](http://maxembedded.com/2015/06/setting-up-avr-gcc-toolchain-on-linux-and-mac-os-x/), and then the UNIX compilation steps can be followed as if you were on Linux.

### Serial Downloader
The data downloader should be simpler to compile due to the fact that all of the serial I/O is done through Qt wrappers. Compilation is done by opening the .pro file in Qt Creator and clicking the green "Run" arrow. This works on all platforms by design, because Qt is awesome. Of course, Qt must be [downloaded](https://www.qt.io/download/) and installed. Please be aware that this is about a gigabyte in size. Depending on your OS, the resulting executable may require special permissions to write to serial devices.

Hardware
--------
### Board and Sensors
The following hardware is required for the Arduino portion of the project. Links are provided to [Adafruit](https://www.adafruit.com/) as an example only, as this is where the components were purchased for the original version of this project. This does not constitute an endorsment of Adafruit Industries. Most of the components can likely be substituted for various alternatives depending on availability, with slight modifications to the source code.

* [Winbond W25Q80BV 1 MByte SPI Flash (1564)](https://www.adafruit.com/product/1564)  
  This is the flash memory used for saving flight data. **It is discontinued.** Similar chips by the same manufacturer could still be used by changing only a few lines according to the datasheet. Alternatively, the memory interface could be rewritten to accomodate other sources of cheap SPI flash memory, such as MicroSD cards (Bonus: more storage space).

* [Adafruit 10-DOF IMU Breakout (1604)](https://www.adafruit.com/product/1604)   
  This breakout board is actually three different sensors on one circuit:   

  1. The L3GD20H is a 3-axis gyroscope allowing for measurement of the rate at which the rocket spins on its vertical axis or tumbles on its pitch and roll axes.
  2. The LSM303 combines a 3-axis compass to determine orientation relative to the fixed magnetic field of the Earth, and a factory-calibrated accelerometer for precise measurement of smaller accelerations (±16g).
  3. The BMP180 pressure sensor allows measurement of static pressure, precise estimation of pressure altitude, as well as air temperature (the last one may not be important on a model rocket, but may be useful for longer flights on, say, makeshift weather balloons).

  All three chips are on the I2C bus, and therefore use only two pins in total on the microcontroller.

* [ADXL377 High-G Triple-Axis Accelerometer](https://www.adafruit.com/product/1413)   
  This breakout board is used as the main accelerometer, capable of measuring accelerations of ±200g. This should be enough for most applications: testing 5-gallon jug rockets pressurized to around 40 psi showed accelerations less than a third of that maximum. The three analog output pins of the board are connected to three analog input pins of the microcontroller. Note that both this circuit and the one described above have x, y and z axes printed on them (or the orientation can be deduced from the datasheets of the individual components). It is important that both sets of axes are aligned as the sensor fusion algorithm makes that assumption.

* [Adafruit Pro Trinket - 3V 12MHz](https://www.adafruit.com/product/2010)   
  The Atmega328p microcontroller board running the actual firmware, this is the "brains" of the device, charged with getting data from all sensors, saving it to memory, and outputting it back to a computer for analysis. It is equipped with a USB bootloader, which will not be used due to the availability of an FTDI chip providing a hardware serial interface. It has a voltage regulator on board, which can output a stable 3.3V from a lithium-ion battery. A battery "backpack" is still useful as an add-on to this board, however, as it allows for both battery removal and in-situ charging via any USB port. Note that Adafruit also sells a slightly higher clock speed version of this board (5V, 16MHz). Do not buy this model, as the SPI memory chips (or MicroSD cards) are strictly 3.3V devices. Connecting them to 5V I/O will result in smoke escaping from any non-level shifted devices on the board. 100% of electrical engineers believe that smoke and shorting are detrimental to electronics.

* [Adafruit Pro Trinket LiIon/LiPoly Backpack Add-On](https://www.adafruit.com/product/2124)   
  As described above, this battery "backpack" supplies the battery voltage directly to the supply side of the microcontroller board's voltage regulator. It allows for easy connection and removal of batteries with a JST connector. When USB power is applied via either the FTDI cable or directly plugging the Pro Trinket's USB port into a 5V supply, the battery is charged.

* Lithium-polymer battery   
  This may be obtained by any means, such as radio-control shops or eBay. Around 150mAh is enough. Just make sure that the battery has a JST plug to fit into the socket on the board, or you will have to solder it directly and lose the ability to remove it. Note that lithium cells are quite flammable and may explode if punctured, smashed or overheated, so make sure to properly protect the circuit before placing it in an actual rocket. The small battery size suggested also helps reduce the mass of the device (which is quite important in rocketry), as well as reducing the potential damage in case of a sudden failure.

* [FTDI Friend](https://www.adafruit.com/product/284)   
  The FTDI Friend is a USB-to-serial adapter enabling serial communication with the Pro Trinket's UART. It is used for controlling the device from the computer, as well as receiving the data once the flight is complete. The adapter also provides 5V power to the battery charger, as if one had plugged a micro-USB cable directly into the Pro Trinket. Other serial devices may also be used, as long as the pin configuration is the same and the voltage is compatible with the Atmega's I/O.

* Various parts   
  It goes without saying that this project requires a stripboard or other prototype board, solder, wire, and various tools such as a soldering iron, wire cutters, needle-nose pliers, etc. The required accessories can be acquired from any electronic parts shop or ordered online, if you don't mind paying for the delivery of a pound-sized spool of lead. The FTDI device uses a mini- rather than micro-USB cable (the kind often used for digital cameras).

### Assembly
The flexibility of AVR microcontrollers' GPIO interface means that there are lots of valid ways of connecting all components.

Usage
-----
Todo.

Credits
-------
Special thanks to [Adafruit](https://www.adafruit.com/) for their amazing tutorials on the various quirks of embeddded programming.

[Qt](https://www.qt.io/) is magic. It makes serial interface programming probably 1000x easier than writing kernel drivers. Also, it allows the exact same source code to run on nearly all operating systems, which is actually impressive for native GUI applications that communicate with low-level hardware. Please use it.
