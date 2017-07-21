#ifndef TEXTPRINTER_H
#define TEXTPRINTER_H

#include "Graphics.h"
#include "../sh1106-spi/SH1106_SPI.h"

struct Point
{
	Point(uint8_t x, uint8_t y) : x(x), y(y / 8), offset(y % 8) { }
	
	uint8_t x;
	uint8_t y;
	uint8_t offset;
};

class Printer
{
	protected:
		Printer(SH1106_SPI* lcd) : p_lcd(lcd) { }
		void offsetBitmapVertically(Bitmap* bitmap, uint8_t offset);
		SH1106_SPI* p_lcd;
};

class TextPrinter : public Printer
{
	public:
		TextPrinter(SH1106_SPI* p_lcd) : Printer(p_lcd) { }
		void print(const char *str, Point p, Font* p_font, uint8_t horizontalOffset = 2);
};

class IconPrinter : public Printer
{
	public:
		IconPrinter(SH1106_SPI* lcd) : Printer(lcd) { }
		void print(Point p, Icon* icon);
};

#endif

