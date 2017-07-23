#include "SDFileService.h"

SDFileService* SDFileService::p_instance = 0;

SDFileService* SDFileService::Instance()
{
  if (!p_instance)
  {
    p_instance = new SDFileService;
	p_instance->begin();
  }

  return p_instance;
}

SDFileService::SDFileService()
{  
	ConfigurationDataRepository config;
	fileCounter = config.fileCounter;
  //fileCounter.setDefault();
}

void SDFileService::begin()
{
	if (!SD.begin(SDCARD_SS_PIN)) 
		Serial.println("Could not initialize SD card.");
}

void SDFileService::create()
{
	create(fileCounter.value() + 1);
}

void SDFileService::create(uint16_t fileCounterValue)
{
	if (isOpen())
		file.close();
	
	this->open(fileCounterValue);
}

void SDFileService::open()
{
	open(fileCounter.value());
}

void SDFileService::open(uint16_t fileCounterValue)
{
	Serial.println(F("Opening file..."));
	char filename[FILE_NAME_SIZE + 1 + FILE_EXTENSION_SIZE];
	getFilename(fileCounterValue, filename);
  
	file = SD.open(filename, FILE_WRITE);

	if (!file)
		ErrorHandler::handleError(Error::SDCARD_ERROR);
}

bool SDFileService::isOpen()
{
	return file;
}

void SDFileService::close()
{
	if (isOpen())
		file.close();
}

void SDFileService::getFilename(uint16_t fileCounterValue, char* filename)
{
	byte index = 0;
	char filePrefix[] = "TRACK";
	char extension[] = "DAT";

	for (byte i = 0; i < FILE_PREFIX_SIZE; i++)
		filename[index++] = filePrefix[i];

	//filename[index++] = (fileCounterValue / 1000) + 48;
	filename[index++] = (fileCounterValue % 1000 / 100) + 48;
	filename[index++] = (fileCounterValue % 100 / 10) + 48;
	filename[index++] = (fileCounterValue % 10) + 48;
	filename[index++] = '.';

	for (byte i = 0; i < FILE_EXTENSION_SIZE; i++)
		filename[index++] = extension[i];

	filename[index] = '\0';
}