#include "DisplayHandler.h"

void DisplayHandler::begin()
{
	lcd.begin();
	
	drawHeader();
	drawData();
}

void DisplayHandler::drawHeader()
{
	char filename[] = "TRACK000";
	drawFilename(filename);
	drawBluetoothIcon();
	drawGpsIcon();
	drawDivider();
}

void DisplayHandler::drawData()
{
	drawDataTitle(MAX_SPEED);
}

void DisplayHandler::drawDataTitle(DataTitle dataTitle)
{
	TextPrinter printer = TextPrinter(&lcd);
	MainFont mainFont = MainFont();

	switch (dataTitle)
	{
		case DISTANCE: printer.print("DISTANCE", Point(48, 24), &mainFont);
			break;
		case MAX_SPEED: printer.print("MAX SPEED", Point(46, 24), &mainFont, 2);
			break;
	}
}

void DisplayHandler::drawDivider()
{
	byte x = 0, y = 2;
	
	while (x < SH1106_X_PIXELS)
	{
		lcd.gotoXY(x++, y);
		lcd.writeLcd(SH1106_DATA, 0x03);
	}
}

void DisplayHandler::drawGpsIcon()
{	
	GpsIcon gpsIcon = GpsIcon();
	IconPrinter iconPrinter = IconPrinter(&lcd);
	iconPrinter.print(Point(118, 0), &gpsIcon);
}

void DisplayHandler::drawBluetoothIcon()
{
	BluetoothIcon btIcon = BluetoothIcon();
	IconPrinter iconPrinter = IconPrinter(&lcd);
	iconPrinter.print(Point(105, 0), &btIcon);
}

void DisplayHandler::drawFilename(char* filename)
{
	TextPrinter printer = TextPrinter(&lcd);
	MainFont mainFont = MainFont();
	printer.print(filename, Point(0, 2), &mainFont);
}

