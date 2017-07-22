/********************************************************************
 This is a "Fast SH1106 Library". It is designed to be used with
 128x64 OLED displays, driven by the SH1106 controller.
 This library uses hardware SPI of your Arduino microcontroller,
 and does not supprt 'software SPI' mode.
 
 Written by Arthur Liberman (aka 'The Coolest'). http://www.alcpu.com
 Special thanks goes out to 'robtillaart' for his help with debugging
 and optimization.

 BSD license, check license.txt for more information.
 All text above must be included in any redistribution.
********************************************************************/

// Version 1.0 -- May 26, 2014

#pragma once
#include "Arduino.h"

// It is very important to wire the LCD correctly. 
// The following is the default wiring configuration for an Atmega168/328 based Arduino:
// PIN_DC    D8 
// PIN_RESET D9 
// PIN_CS	 D10
// PIN_SDIN  D11 
// PIN_SCLK  D13 

// You may change pins D/C, Reset and CS to map them to different pins on your Arduino board. 
// Please keep SDA/DI and SCL/CLK connected to your Arduino's MOSI and SCK (hardware SPI) pins.
// You can remap the LCD control pins by changing the following '#define' values:
// Please refer to the pin/port mapping for your Arduino device:
// http://arduino.cc/en/Hacking/PinMapping168
// http://arduino.cc/en/Hacking/PinMapping2560
// http://arduino.cc/en/Hacking/PinMapping32u4
// Pins labeled Px (PB, PC, etc.) stand for PORTx.
// The current version of this library only allows the use of one port for the control pins.
// Pins are mapped in binary order. Valid values are 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80.
// Px0 is the LSB pin of the port, which in turn is represented by the hexadecimal number 0x01. 
// Px7 is the MSB pin of the port, which in turn is represented by the hexadecimal number 0x80.

// This is the port where the LCD is connected.
#define SH1106_PORT			PORTB
#define SH1106_DDR			DDRB	// Should be DDRx, x = port name (B, C, D, etc.)
						
#define PIN_DC				0x01	// D8
#define PIN_RESET			0x02	// D9
#define PIN_CS				0x04	// D10
#define PINS_CS_DC			(PIN_DC | PIN_CS)

// When DC is '1' the LCD expects data, when it is '0' it expects a command.
#define SH1106_COMMAND		0 
#define SH1106_DATA			PIN_DC

// You may find a different size screen, but this one is 128 by 64 pixels
#define SH1106_X_PIXELS		128
#define SH1106_Y_PIXELS		64
#define SH1106_ROWS			8


// Functions gotoXY, writeBitmap, renderString, writeLine and writeRect
// will return SH1106_SUCCESS if they succeed and SH1106_ERROR if they fail.
#define SH1106_SUCCESS		1
#define SH1106_ERROR		0


class SH1106_SPI
{
public:
	SH1106_SPI();	
	
	///***************************************************************************************************************
	// invert - True for inverted display and False for normal.
	// fastSpi - True enables a /2 SPI divider, False leaves the divider at the default /4.
	// contrast - Sets the contrast of the display, valid values are in the range of 0 - 255.
	// Vpp - Sets the charge pump voltage for the display, 0 = 6.4V, 1 = 7.4V, 2 = 8.0V (controller default), 3 = 9.0V
	///***************************************************************************************************************
	void begin(bool invert = false, bool fastSpi = false, uint8_t contrast = 128, uint8_t Vpp = 0);
	void clear();
	uint8_t clearArea(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
	uint8_t gotoXY(uint8_t x, uint8_t y);
	uint8_t writeBitmap(const uint8_t *bitmap, uint8_t x, uint8_t y, uint8_t width, uint8_t height);
	//void init(void);
	void writeLcd(uint8_t dataOrCommand, uint8_t data);
	void writeLcd(uint8_t dataOrCommand, const uint8_t *data, uint16_t count);

private:
	uint8_t m_Column;
	uint8_t m_Line;
	void advanceXY(uint8_t columns);
};