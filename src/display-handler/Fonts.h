#ifndef FONTS_H
#define FONTS_H

#include "Arduino.h"

#define FONT_MAIN_ELEMENT_SIZE 16

struct Bitmap
{
  byte* value;
  uint16_t width;
  uint16_t height;
};

class Font
{
  public:
    virtual Bitmap getBitmapFromCharacter(char character) = 0;
};

class MainFont : public Font
{
  public:
    Bitmap getBitmapFromCharacter(char character);
    uint16_t getArrayElementSize() { return FONT_MAIN_ELEMENT_SIZE - 2; }
    
  private:
    static const byte font_digits[10][FONT_MAIN_ELEMENT_SIZE];
    static const byte font_letters[26][20];
};

class Icon
{
  public:
    virtual Bitmap getBitmap() = 0;
};

class BluetoothIcon : public Icon
{
  public:
    Bitmap getBitmap();
  private:
    static const byte icon_bluetooth[20];
};

#endif
