#ifndef EEPROM_I2C_H
#define EEPROM_I2C_H

#include "Arduino.h"
#include <Wire.h>

#define MEMORY_SIZE 4096
#define EEPROM_ADDRESS 0x50

class EEPROM_I2C
{
  public:
    EEPROM_I2C();
	bool check();
    byte readByte(uint16_t address);
    void readPage(uint16_t address, uint16_t length, byte *data);
    void writeByte(uint16_t address, byte data);
    void writePage(uint16_t address, byte data[], uint8_t length);
};
#endif