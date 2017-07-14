#include "EEPROM_I2C.h"

EEPROM_I2C::EEPROM_I2C()
{
  Wire.begin();
}

bool EEPROM_I2C::check()
{
  Wire.beginTransmission(EEPROM_ADDRESS);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
  
  Wire.requestFrom(EEPROM_ADDRESS, 1);
  for (int i = 0; i < 5; i++)
  {
    if (Wire.available() > 0) { return true; }
	delay(1);
  }
  
  return false;
}

//     MEMORY READ METHODS
/* * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * */

void EEPROM_I2C::readPage(uint16_t address, uint16_t length, byte *data)
{ 
  for (int i = 0; i < length; i++)
  {
    *(data + i) = readByte(address + i);
  }
}

byte EEPROM_I2C::readByte(uint16_t address)
{
  byte data;
  
  Wire.beginTransmission(EEPROM_ADDRESS);
  Wire.write(address >> 8);
  Wire.write(address);
  Wire.endTransmission();
  
  Wire.requestFrom(EEPROM_ADDRESS, 1);
  for (int i = 0; i < 5; i++)
  {
    if (Wire.available() > 0) { return Wire.read(); }
	delay(1);
  }

  Serial.println("Memory fail.");
}

//     MEMORY WRITE METHODS
/* * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * */

void EEPROM_I2C::writePage(uint16_t address,  byte *data, uint8_t length)
{ 
  for (int i = 0; i < length; i++)
  {
    writeByte(address + i, *(data + i));
	  delay(7);
  }
}

void EEPROM_I2C::writeByte(uint16_t address, byte data)
{
   Serial.println(data, BIN);
    
  Wire.beginTransmission(EEPROM_ADDRESS);
  Wire.write(address >> 8);
  Wire.write(address);
  
  Wire.write(data);    
  Wire.endTransmission();
}

