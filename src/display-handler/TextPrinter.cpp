#include "TextPrinter.h"

byte* createCopyOfArray(byte* copyFrom, uint8_t oldLength, uint8_t newLength, bool clear = false)
{
	byte* copyTo = new byte[newLength];
	
	for (uint8_t i = 0; i < oldLength; i++)
		copyTo[i] = copyFrom[i];
	
	if (clear && newLength > oldLength )
		for (uint8_t i = oldLength; i < newLength; i++)
			copyTo[i] = 0x00;
	
	return copyTo;
}

void Printer::offsetBitmapVertically(Bitmap* p_bitmap, uint8_t offset)
{
	uint8_t* width = &p_bitmap->width;
	uint8_t* height = &p_bitmap->height;
	byte* array = p_bitmap->value;
		
	if ((*height + offset) / 8 > *height / 8)
	{	
		uint8_t newLength = Bitmap::arrayLength(*width, *height + offset);
		byte* newArray = createCopyOfArray(array, p_bitmap->arrayLength(), newLength, true);
		delete [] array;
		
		*height += offset;
		p_bitmap->value = array = newArray;
	}
	
	for (byte i = 0; i < *width; i++)
	{
		byte previousValue = 0;
		for (byte j = 0; j <= *height / 8; j++)
		{
			byte index = i + *width * j;
			byte tmp = array[index] >> 8 - offset;
			array[index] = (array[index] << offset) | previousValue;
			previousValue = tmp;
		}
	}
}

void Printer::clearBitmapArea(Font* p_font, uint8_t x, uint8_t y, uint8_t width, uint8_t height)
{
	byte* array = p_font->createEmptyBitmapArray(width, height);
	p_lcd->writeBitmap(array + 2, x, y, width, height);
	delete [] array;
}

void TextPrinter::print(char *str, Point p, Font* p_font, uint8_t horizontalOffset, bool alignRight, uint8_t fixedWidth)
{
	while (*str) 
	{
		Bitmap* p_bitmap = p_font->getBitmapFromCharacter(*str);
			
		if (p.offset > 0)
			offsetBitmapVertically(p_bitmap, p.offset);
		
		uint8_t width = p_bitmap->width;
		uint8_t height = p_bitmap->height;
					
		if (alignRight)
		{
			uint8_t x = p.x, y = p.y;
			
			if (fixedWidth > width)
			{
				clearBitmapArea(p_font, p.x - fixedWidth, p.y, fixedWidth, height);
				x -= (fixedWidth - width) / 2;
				
				p_lcd->writeBitmap(p_bitmap->value, x - width, y, width, height);
				p.x -= (fixedWidth + horizontalOffset);
			}
			else
			{
				
				p_lcd->writeBitmap(p_bitmap->value, x - width, y, width, height);
				p.x -= (width + horizontalOffset);
			}
		}
		else
		{
			p_lcd->writeBitmap(p_bitmap->value, p.x, p.y, width, height);
			p.x += width + horizontalOffset;
		}
		str++;
		
		delete p_bitmap;
	}	
}

void IconPrinter::print(Point p, Icon* p_icon)
{
	Bitmap* p_bitmap = p_icon->getBitmap();
	
	uint8_t width = p_bitmap->width;
	uint8_t height = p_bitmap->height;
	
	if (p.offset > 0)
			offsetBitmapVertically(p_bitmap, p.offset);
		
	p_lcd->writeBitmap(p_bitmap->value, p.x, p.y, width, height);
	
	delete p_bitmap;
}

