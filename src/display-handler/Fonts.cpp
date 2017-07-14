#include "Fonts.h"

const byte BluetoothIcon::icon_bluetooth[20] PROGMEM
{
  0x09, 0x0f, 0x10, 0x30, 0x60, 0xe0, 0xff, 0xc6, 0x6c, 0x38, 0x10, 0x04, 0x06, 0x03, 0x03, 0x7f, 0x31, 0x1b, 0x0e, 0x04
};

const byte MainFont::font_digits [10][FONT_MAIN_ELEMENT_SIZE] PROGMEM
{
  { 0x07, 0x0c, 0xf8, 0x06, 0x01, 0x01, 0x01, 0x06, 0xf8, 0x01, 0x06, 0x08, 0x08, 0x08, 0x06, 0x01 },  // 48 - 0
  { 0x05, 0x0c, 0x04, 0x02, 0xff, 0x00, 0x00, 0x08, 0x08, 0x0f, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00 },  // 49 - 1
  { 0x07, 0x0c, 0x06, 0x01, 0x01, 0x81, 0x41, 0x22, 0x1c, 0x0c, 0x0a, 0x09, 0x08, 0x08, 0x08, 0x0c },  // 50 - 2
  { 0x07, 0x0c, 0x00, 0x02, 0x21, 0x21, 0x31, 0x4e, 0x80, 0x04, 0x08, 0x08, 0x08, 0x08, 0x04, 0x03 },  // 51 - 3
  { 0x07, 0x0c, 0x80, 0x60, 0x18, 0x06, 0xff, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x0f, 0x01, 0x01 },  // 52 - 4
  { 0x07, 0x0c, 0x00, 0x1f, 0x11, 0x11, 0x11, 0x21, 0xc1, 0x04, 0x08, 0x08, 0x08, 0x08, 0x04, 0x03 },  // 53 - 5
  { 0x07, 0x0c, 0xf8, 0x44, 0x22, 0x21, 0x21, 0x41, 0x80, 0x03, 0x04, 0x08, 0x08, 0x08, 0x04, 0x03 },  // 54 - 6
  { 0x07, 0x0c, 0x07, 0x01, 0x01, 0x01, 0xc1, 0x39, 0x07, 0x00, 0x00, 0x00, 0x0e, 0x01, 0x00, 0x00 },  // 55 - 7
  { 0x07, 0x0c, 0x8c, 0x52, 0x21, 0x21, 0x21, 0x52, 0x8c, 0x03, 0x04, 0x08, 0x08, 0x08, 0x04, 0x03 },  // 56 - 8
  { 0x07, 0x0c, 0x1c, 0x22, 0x41, 0x41, 0x41, 0x22, 0xfc, 0x00, 0x08, 0x08, 0x08, 0x08, 0x04, 0x03 },  // 57 - 9
};

const byte MainFont::font_letters [26][20] PROGMEM
{
  { 0x09, 0x0b, 0x00, 0x80, 0x70, 0x4c, 0x43, 0x4c, 0x70, 0x80, 0x00, 0x04, 0x07, 0x04, 0x00, 0x00, 0x00, 0x04, 0x07, 0x04 }, // 65 - A
  { }, // 66 - B
  { 0x08, 0x0b, 0xfc, 0x02, 0x01, 0x01, 0x01, 0x01, 0x02, 0x07, 0x01, 0x02, 0x04, 0x04, 0x04, 0x04, 0x02, 0x00, 0x00, 0x00 }, // 67 - C
  { }, // 68 - D
  { }, // 69 - E
  { }, // 70 - F
  { }, // 71 - G
  { }, // 72 - H
  { }, // 73 - I
  { }, // 74 - J
  { 0x09, 0x0b, 0x01, 0xff, 0x41, 0x30, 0x48, 0x85, 0x03, 0x01, 0x00, 0x04, 0x07, 0x04, 0x00, 0x00, 0x00, 0x05, 0x06, 0x04 }, // 75 - K
  { }, // 76 - L
  { }, // 77 - M
  { }, // 78 - N
  { }, // 79 - O
  { }, // 80 - P
  { }, // 81 - Q
  { 0x08, 0x0b, 0x01, 0xff, 0x21, 0x61, 0xa1, 0x12, 0x0c, 0x00, 0x04, 0x07, 0x04, 0x00, 0x00, 0x01, 0x06, 0x04, 0x00, 0x00 }, // 82 - R
  { }, // 83 - S
  { 0x07, 0x0b, 0x03, 0x01, 0x01, 0xff, 0x01, 0x01, 0x03, 0x00, 0x00, 0x04, 0x07, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // 84 - T
  { }, // 85 - U
  { }, // 86 - V
  { }, // 87 - W
  { }, // 88 - X
  { }, // 89 - Y
  { } // 90 - Z
};

Bitmap BluetoothIcon::getBitmap()
{
  Bitmap bitmap;

  bitmap.value = icon_bluetooth + 2;
  bitmap.width = pgm_read_word(bitmap.value - 2);
  bitmap.height = pgm_read_word(bitmap.value - 1);

  return bitmap;
}

Bitmap MainFont::getBitmapFromCharacter(char character)
{
  Bitmap bitmap;
  
  if (character >= 48 && character <= 57)
    bitmap.value =  font_digits[character - 48] + 2;
  else if (character >= 65 && character <= 90)
    bitmap.value =  font_letters[character - 65] + 2;

  bitmap.width = pgm_read_word(bitmap.value - 2);
  bitmap.height = pgm_read_word(bitmap.value - 1);
    
  return bitmap;
}

