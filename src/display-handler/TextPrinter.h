#ifndef FONTHANDLER_H
#define FONTHANDLER_H

#include "Fonts.h"
#include "SH1106_SPI.h"

struct Point
{
  Point(byte x, byte y) : x(x), y(y) { }
  byte x = 0;
  byte y = 0;
};

class Printer
{
  protected:
    Printer(SH1106_SPI* lcd) :
      p_lcd(lcd) { }
      
    SH1106_SPI* p_lcd;
};

class TextPrinter : public Printer
{
  public:
    TextPrinter(SH1106_SPI* p_lcd) : Printer(p_lcd) { }
    void print(const char *str, Point p, Font* p_font);
};

class IconPrinter : public Printer
{
  public:
    IconPrinter(SH1106_SPI* lcd) :
      Printer(lcd) { }
    void print(Point p, Icon* icon);
};

#endif

