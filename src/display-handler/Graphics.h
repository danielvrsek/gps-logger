#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Arduino.h"

#define FONT_MAIN_ELEMENT_SIZE 16

struct Bitmap
{
	public:
		Bitmap(const byte* bitmapArray);
		Bitmap(byte* bitmapArray);
		~Bitmap() { delete [] value; }
	
		uint8_t arrayLength() { return arrayLength(width, height); } 
		static uint8_t arrayLength(uint8_t width, uint8_t height) { return width * ((height / 8) + 1); } // TODO potencional bug when height % 8 == 0
		
		byte* value;
		uint8_t width;
		uint8_t height;
};

class Font
{
	public:
		virtual Bitmap* getBitmapFromCharacter(char character) = 0;
		byte* createEmptyBitmapArray(uint8_t width, uint8_t height);
};

class MainFont : public Font
{
	public:
		Bitmap* getBitmapFromCharacter(char character);
};

class SpeedFont : public Font
{
	public:
		Bitmap* getBitmapFromCharacter(char character);
};

class UnitsFont : public Font
{
	public:
		Bitmap* getBitmapFromCharacter(char character);
};

class DataFont : public Font
{
	public:
		Bitmap* getBitmapFromCharacter(char character);
};

class Icon
{
	public:
		virtual Bitmap* getBitmap() = 0;
		//virtual Bitmap getBitmap(uint8_t offset) = 0;
};

class BluetoothIcon : public Icon
{
	public:
		Bitmap* getBitmap();
		//Bitmap getBitmap(uint8_t offset) { return offsetBitmap(getBitmap(), offset); }
};

class GpsIcon : public Icon
{
	public:
		Bitmap* getBitmap();
		//Bitmap getBitmap(uint8_t offset) { return offsetBitmap(getBitmap(), offset); }
};

#endif
