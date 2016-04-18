ModelRocketAHRS
===============
An Arduino project to measure acceleration and pressure altitude on small model rockets.

Description
-----------
This project contains two programs: One is an Arduino executable designed to be installed on a board with a particular hardware configuration (see the relevant section below). The other is a serial communication utility that allows sending commands to the device or the reading and parsing of the data contained therein (only the csv format is currently supported). The entire project is licensed under the permissive [New BSD License](./LICENSE), and all recommended hardware is easily available.

Hardware
--------
### Board and sensors
The following hardware is required for the Arduino portion of the project. Links are provided to [Adafruit](https://www.adafruit.com/) as an example only, as this is where the components were purchased for the original version of this project. This does not constitute an endorsment of Adafruit Industries. Most of the components can likely be substituted for various alternatives depending on availability, with slight modifications to the source code.

* [Winbond W25Q80BV 1 MByte SPI Flash (1564)](https://www.adafruit.com/products/1564)  
  This is the flash memory used for saving flight data. **It is discontinued.** Similar chips by the same manufacturer could still be used by changing only a few lines according to the specifications. Alternatively, the memory interface could be rewritten to accomodate other sources of cheap SPI flash memory, such as MicroSD cards (Bonus: more storage space).

### Assembly
The flexibility of AVR microcontrollers' GPIO interface means that there are lots of valid ways of connecting all components.

Credits
-------
Special thanks to [Adafruit](https://www.adafruit.com/) for their amazing tutorials on the various quirks of embeddded programming.

[Qt](https://www.qt.io/) is magic. It makes serial interface programming probably 1000x easier than writing kernel drivers. Also, it allows the exact same source code to run on nearly all operating systems, which is actually impressive for native GUI applications that communicate with low-level hardware. Please use it.
