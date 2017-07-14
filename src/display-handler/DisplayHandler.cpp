#include "DisplayHandler.h"

byte array [][3] = 
{
  { 0x00, 0x00, 0x00 },
  { 0x01, 0x01, 0x01 },
  { 0x02, 0x02, 0x02 }
};

void DisplayHandler::begin()
{
  lcd.begin();

  drawDivider();
  drawFilename();

  BluetoothIcon btIcon = BluetoothIcon();
  IconPrinter iconPrinter = IconPrinter(&lcd);
  iconPrinter.print(Point(105, 0), &btIcon);
}

void DisplayHandler::drawDivider()
{
  byte x = 0;
  byte y = 2;
  
  while (x < SH1106_X_PIXELS)
  {
    Serial.print(lcd.gotoXY(x++, y));
    lcd.writeLcd(SH1106_DATA, 0x03);
  }
}

void DisplayHandler::drawFilename()
{
  TextPrinter printer = TextPrinter(&lcd);
  MainFont mainFont = MainFont();
  printer.print("TRCK0000", Point(0, 0), &mainFont);
}

