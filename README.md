WaterRocketAHRS
===============
An Arduino project to measure acceleration and pressure altitude on small 
model rockets.

Description
-----------
This project contains two programs: One is an Arduino executable designed 
to be installed on a board with a particular hardware configuration 
(see the relevant section below). The other is a command-line serial 
communication utility that allows sending commands to the device or the 
reading and parsing of the data contained therein (only the csv format is 
currently supported). The entire project is licensed under the permissive 
[New BSD License](./LICENSE), and all the recommanded hardware is 
easily available.

Hardware
--------
### Board and sensors
The following hardware is required for the Arduino portion of the project. 
Links are provided to [Adafruit](https://www.adafruit.com/) as an example 
only, as this is where the components were purchased for the original 
version of this project. This does not constitute an endorsment of Adafruit 
Industries. Most of the components can likely be substituted for various 
alternatives depending on availability, with slight 
modifications to the source code.

#### Todo

### PC portion
To run the command-line serial utility and communicate with the board, 
a computer with up-to-date FTDI drivers is required. The utility expects 
to see the FTDI chip as a Virtual COM Port (VCP), which means you will 
need to get the VCP drivers. Windows and Mac users will need to 
[download](http://www.ftdichip.com/Drivers/VCP.htm) the drivers from 
FTDI's website. Linux users using a recent kernel version will likely 
have those drivers built-in and will not need any extra steps.

In order to build the software and upload it to the board, you will need 
the Arduino IDE. Note that the ability to install 3rd party boards from 
the IDE is **required** and that the IDE **must** therefore be version 1.6.4 
or later. In addition, Linux users who want the ability to install the 
software from the Makefile must have both 
[Arduino-Makefile](https://github.com/sudar/Arduino-Makefile#installation) 
and [pySerial](https://github.com/sudar/Arduino-Makefile#pyserial) installed.

Credits
-------
Special thanks to Adafruit for their amazing tutorials on various 
quirks of embeddded programming. 
The serial communication library for the PC portion of the code comes from 
GitHub user [wjwwood](https://github.com/wjwwood/serial). 
The Makefile used in this project references 
[this Github project](https://github.com/sudar/Arduino-Makefile).
