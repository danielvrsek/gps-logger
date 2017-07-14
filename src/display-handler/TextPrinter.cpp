#include "TextPrinter.h"

void TextPrinter::print(const char *str, Point p, Font* p_font)
{
  while (*str) 
  {
    Bitmap bitmap;
  
    bitmap = p_font->getBitmapFromCharacter(*str);
    p_lcd->writeBitmap(bitmap.value, p.x, p.y, bitmap.width, bitmap.height);

    p.x += bitmap.width + 2;
    str++;
  }
}

void IconPrinter::print(Point p, Icon* p_icon)
{
  Bitmap bitmap;
  bitmap = p_icon->getBitmap();
  p_lcd->writeBitmap(bitmap.value, p.x, p.y, bitmap.width, bitmap.height);
}

