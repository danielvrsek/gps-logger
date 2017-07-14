#ifndef DISPLAYHANDLER_H
#define DISPLAYHANDLER_H

#include <SPI.h>
#include "SH1106_SPI.h"
#include "Fonts.h"
#include "TextPrinter.h"

class DisplayHandler
{
  public:
    void begin();
    void drawDivider();
    void drawFilename();
    
  private:
    SH1106_SPI lcd;
};

#endif

