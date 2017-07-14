#include "Configuration.h"

EEPROM_I2C ConfigData::eeprom;

uint16_t ConfigData::readValueFromMemory(uint16_t address, byte size)
{  
  if (!eeprom.check())
    ErrorHandler::handleError(Error::EEPROM_ERROR);

  uint16_t temp = 0;

  for (byte i = 0; i < size; i++)
    temp = temp | eeprom.readByte(address) >> 8 * i;
    
  return temp;
}

void ConfigData::writeValueToMemory(uint16_t address,uint16_t data, byte size)
{
  if (!eeprom.check())
    ErrorHandler::handleError(Error::EEPROM_ERROR);

  for (byte i = 0; i < size; i++)
    eeprom.writeByte(address + i, data >> 8 * i);    
}

FileCounter FileCounter::operator++(int)  
{
  FileCounter temp = *this;
  increaseCounterValue();
  return temp;  
}

