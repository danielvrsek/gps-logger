#include "TextPrinter.h"

void Printer::offsetBitmapVertically(Bitmap* bitmap, uint8_t offset)
{
	byte length = bitmap->arrayLength();
	byte* array = bitmap->value;
	
	byte previousValue = 0;
	
	for (byte i = 0; i < bitmap->width; i++)
	{
		byte previousValue = 0;
		for (byte j = 0; j <= bitmap->height / 8; j++)
		{
			byte index = i + bitmap->width * j;
			
			byte tmp = array[index] >> 8 - offset;
			array[index] = (array[index] << offset) | previousValue;
			previousValue = tmp;
		}
	}
}

void TextPrinter::print(const char *str, Point p, Font* p_font, uint8_t horizontalOffset)
{
	while (*str) 
	{
		Bitmap bitmap = p_font->getBitmapFromCharacter(*str);
		if (p.offset > 0)
			offsetBitmapVertically(&bitmap, p.offset);
		p_lcd->writeBitmap(bitmap.value, p.x, p.y, bitmap.width, bitmap.height);
		p.x += bitmap.width + horizontalOffset;
	
		str++;
	}	
}

void IconPrinter::print(Point p, Icon* p_icon)
{
	Bitmap bitmap = p_icon->getBitmap();
	if (p.offset > 0)
			offsetBitmapVertically(&bitmap, p.offset);
	p_lcd->writeBitmap(bitmap.value, p.x, p.y, bitmap.width, bitmap.height);
}

