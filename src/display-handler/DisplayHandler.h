#ifndef DISPLAYHANDLER_H
#define DISPLAYHANDLER_H

#include <SPI.h>
#include "../sh1106-spi/SH1106_SPI.h"
#include "Graphics.h"
#include "TextPrinter.h"

enum DataTitle
{
	DISTANCE,
	MAX_SPEED
};

class DisplayHandler
{
	public:
		void begin();
		void drawFilename(char* filename);
		void drawBluetoothIcon();
		void drawGpsIcon();
		void drawDataTitle(DataTitle titleText);
		void drawData(uint32_t data, uint8_t decimalPlaces);
		void drawSpeed(uint8_t speed);
		
	private:
		void drawHeader();
		void drawDefaultData();
		void drawDivider();
		void drawSpeedUnits();
		void drawDataUnits();
		SH1106_SPI lcd;
		TextPrinter textPrinter = TextPrinter(&lcd);
		IconPrinter iconPrinter = IconPrinter(&lcd);
};

#endif

