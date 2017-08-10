#ifndef SDFILESERVICE_H
#define SDFILESERVICE_H

#include <SdFat.h>
#include <SPI.h>
#include "ErrorHandler.h"
#include "ConfigurationDataRepository.h"

#define FILE_NAME_SIZE 8
#define FILE_PREFIX_SIZE 4
#define FILE_EXTENSION_SIZE 3

#define SDCARD_SS_PIN 6

class SDFileService
{
	public:
		static SDFileService* Instance();
		void begin();
		
		void create();
		void create(uint16_t fileCounterValue);
		void open();
		void open(uint16_t fileCounterValue);
		bool isOpen();
		void close();
		void getFilename(uint16_t fileCounterValue, char* filename);
		
		File file;
		
	private:
		SDFileService();
		FileCounter fileCounter;
		SdFat SD;
		
		static SDFileService* p_instance;
};

#endif