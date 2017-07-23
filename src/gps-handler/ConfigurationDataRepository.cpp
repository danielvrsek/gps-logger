#include "ConfigurationDataRepository.h"

uint16_t ConfigData::readValueFromMemory(uint16_t address, byte size)
{  
  uint16_t temp = 0;

  for (byte i = 0; i < size; i++)
    temp = temp | EEPROM.read(address) >> 8 * i;
    
  return temp;
}

void ConfigData::writeValueToMemory(uint16_t address,uint16_t data, byte size)
{
  for (byte i = 0; i < size; i++)
    EEPROM.write(address + i, data >> 8 * i);    
}

FileCounter FileCounter::operator++(int)  
{
  FileCounter temp = *this;
  increaseCounterValue();
  return temp;  
}