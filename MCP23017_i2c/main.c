/*
 * MCP23017_i2c.c
 *
 * This program demonstrates use of a MCP23017 port expander and I2C.
 * It sets IODIRA and IODIRB registers to output, then toggles all 16 pins with a ~250ms delay  
 * MCP23017 Data sheet: http://ww1.microchip.com/downloads/en/DeviceDoc/20001952C.pdf
 * Other resources: https://github.com/g4lvanix/I2C-master-lib (Atmega328 I2C library)
 * http://indigoid.blogspot.dk/2013/06/mcp23017-and-bus-pirate.html (BUS pirate example)
 * Created: 10-12-2017 18:10:32
 * Author : NS
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include "i2c_master.h"
#include <util/delay.h>

//defines for MCP23017 - prevent magic numbers
#define MCP23017 0x40
#define IODIRA 0x00 //Direction register of pins on GPIOA
#define IODIRB 0x01 //Direction register of pins on GPIOB
#define GPINTENB 0x05 //interrupt on change from GPIOB
#define DEFVALB 0x07 //Value to compare with to trigger interrupt
#define INTCONB 0x09 //Use DEFVAL to compare instead of the previous state of GPIOB
#define INTCAPB 0x11 //Capture of port on interrupt B
#define GPIOA 0x12 //address of GPIOA which is used for outputs
#define GPIOB 0x13 //address of GPIOB which is used for inputs
#define IOCON 0x14 //IOCON B register for setting up interrupt pin on GPIOB
#define PULLUPB 0x0D //Register for pull up resistors on GPIOB
#define PULLUPA 0x0C //Register for pull up resistors on GPIOA
#define OLATA 0x14 //output latch A

//function prototypes
void init_MCP23017 (void);

int main(void)
{

	i2c_init();
	init_MCP23017();
	
	while (1)
	{
		
		i2c_start(MCP23017); //Select I2C address 0x40 (0b0100000)
		i2c_write(GPIOB); // Select GPIOB register (0x13)
		i2c_write(0xFF); // Set entire GPI0B port high
		i2c_stop(); //send stop bit
		_delay_ms(250);
		
		i2c_start(MCP23017); //Select I2C address 0x40 (0b0100000)
		i2c_write(GPIOA); // Select GPIOA register (0x12)
		i2c_write(0xFF); // Set entire GPI0A port high
		i2c_stop(); //send stop bit
		_delay_ms(250);
		
		i2c_start(MCP23017); //Select I2C address 0x40 (0b0100000)
		i2c_write(GPIOB); // Select GPIOB register (0x13)
		i2c_write(0x00); // Set entire GPI0B port low
		i2c_stop(); //send stop bit
		
		_delay_ms(250);
		i2c_start(MCP23017); //Select I2C address 0x40 (0b0100000)
		i2c_write(GPIOA); // Select GPIOA register (0x12)
		i2c_write(0x00); // Set entire GPI0A port low
		i2c_stop(); //send stop bit
		_delay_ms(250);
	}
	return 0;
}

void init_MCP23017 (void)
{
	i2c_start(MCP23017); //Select I2C address 0x40 (0b0100000)
	i2c_write(IODIRA); // Select IODIRA register address (0x00)
	i2c_write(0x00); // Set IODIRA to output
	i2c_write(0x00); // Set IODIRB to output
	i2c_stop(); //send stop bit
}

