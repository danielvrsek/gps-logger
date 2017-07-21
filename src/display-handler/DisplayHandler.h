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
    
	private:
		void drawHeader();
		void drawData();
		void drawDivider();
		SH1106_SPI lcd;
};

#endif

