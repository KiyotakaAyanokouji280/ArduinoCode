# Set Up Arduino development without the IDE

Things I take into account for this project:
1. Using only C to code the files.
2. Using only the command line for all purposes hereafter (Vim for editing code).

## Installing pre-requisites

### AVR Toolchain Installation

`sudo apt-get update`
`sudo apt-get install gcc-avr binutils-avr avr-libc gdb-avr avrdude`

This will install all required files for development just using the command line.

## Set up the code

Put the following two libraries if wishing to program the microcontroller in C:
`#include <avr/io.h>
#include <util/delay.h>
//followed by the rest of the code`

## Burn to controller and see output

### Compiling the code:
Use the following command in the same directory as the C file just written:
`avr-gcc -mmcu=atmega328p -o output.elf firstembeddedprogram.c`

### Generating the output HEX file
The file generated here in the same directory will be burnt onto the Arduino UNO in the next step
`avr-objcopy -O ihex -R .eeprom output.elf output.hex` 

### Burning the file onto the board
Use this command to burn the file onto the board. Make sure to replace the 'atmega328p' with the controller model mentioned on the board. Also make sure to change '/dev/ttyACM0' to the port you are using. Might be '/dev/ttyUSB0' or something like that. 
`avrdude -c arduino -p atmega328p -P /dev/ttyACM0 -b 115200 -U flash:w:output.hex`




