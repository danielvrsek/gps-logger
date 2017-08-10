#include "DisplayHandler.h"

void DisplayHandler::begin()
{
	lcd.begin();
	
	drawHeader();
	drawDefaultData();
}

void DisplayHandler::drawHeader()
{
	char filename[] = "TRACK000";
	drawFilename(filename);
	drawBluetoothIcon();
	drawGpsIcon();
	drawDivider();
}

void DisplayHandler::drawDefaultData()
{
	drawDataTitle(DISTANCE);
	
	drawSpeed(0);
	drawSpeedUnits();
	drawData(0, 1);
	drawDataUnits();
}

void DisplayHandler::drawDataTitle(DataTitle dataTitle)
{
	char distance_text[] = "DISTANCE";
	char maxspeed_text[] = "MAX SPEED";
	
	MainFont mainFont = MainFont();

	switch (dataTitle)
	{
		case DISTANCE: textPrinter.print(distance_text, Point(48, 24), &mainFont);
			break;
		case MAX_SPEED: textPrinter.print(maxspeed_text, Point(46, 24), &mainFont, 2);
			break;
	}
}

void DisplayHandler::drawSpeed(uint8_t speed)
{
	if (speed > 99) return;
	
	char speedChars[3];
	
	byte index = 0;
	
	uint8_t tens = speed % 100 / 10;
	uint8_t hundreds = speed % 1000 / 100;
	
	speedChars[index++] = speed % 10 + 48;
	speedChars[index++] = tens + 48;
	if (hundreds > 0)
		speedChars[index++] = hundreds;
	
	speedChars[index] = '\0';
	
	SpeedFont speedFont = SpeedFont();
	textPrinter.print(speedChars, Point(39, 24), &speedFont, 2, true, 16);
}

void DisplayHandler::drawSpeedUnits()
{
	char units[] = "km/h";
	
	UnitsFont unitsFont = UnitsFont();
	textPrinter.print(units, Point(7, 51), &unitsFont, 0);
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

void DisplayHandler::drawData(uint32_t data, uint8_t decimalPlaces)
{	
	if (data > 99999) return;

	char dataChars[7];
	
	byte index = 0;
	if (decimalPlaces > 0)
	{
		for (uint8_t i = 0; i < decimalPlaces; i++)
		{
			dataChars[index++] = data % 10 + 48;
			data = data / 10;
		}
		dataChars[index++] = ',';
	}

	uint8_t tens = data % 100 / 10;
	uint8_t hundreds = data % 1000 / 100;
	uint16_t thousands = data % 10000 / 1000;
	
	dataChars[index++] = data % 10 + 48;
	if (tens > 0)
		dataChars[index++] = tens + 48;
	if (hundreds > 0)
		dataChars[index++] = hundreds + 48;
	if (thousands > 0)
		dataChars[index++] = thousands + 48;
	
	dataChars[index] = '\0';
	
	DataFont dataFont = DataFont();
	lcd.clearArea(50, 44, 56, 17);
	textPrinter.print(dataChars, Point(106, 44), &dataFont, 2, true);
}

void DisplayHandler::drawDataUnits()
{
	char units[] = "km";
	
	UnitsFont unitsFont = UnitsFont();
	textPrinter.print(units, Point(109, 47), &unitsFont, 0);
}

void DisplayHandler::drawGpsIcon()
{	
	GpsIcon gpsIcon = GpsIcon();
	IconPrinter iconPrinter = IconPrinter(&lcd);
	iconPrinter.print(Point(118, 0), &gpsIcon);
}

void DisplayHandler::clearGpsIcon()
{
	lcd.clearArea(118, 0, 9, 15);
}

void DisplayHandler::clearBluetoothIcon()
{
	lcd.clearArea(105, 0, 9, 15);
}

void DisplayHandler::drawBluetoothIcon()
{
	BluetoothIcon btIcon = BluetoothIcon();
	iconPrinter.print(Point(105, 0), &btIcon);
}

void DisplayHandler::drawFilename(char* filename)
{
	TextPrinter printer = TextPrinter(&lcd);
	MainFont mainFont = MainFont();
	//lcd.clearArea(0, 3, 80, 11);
	textPrinter.print(filename, Point(0, 2), &mainFont);
}

