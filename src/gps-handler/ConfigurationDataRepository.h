#ifndef CONFIGURATIONDATAREPOSITORY_H
#define CONFIGURATIONDATAREPOSITORY_H

#include "Arduino.h"
#include <EEPROM.h>

#define FILE_COUNTER_ADDRESS 0x00
#define FILE_COUNTER_SIZE 2
#define FILE_COUNTER_DEFAULT 0

#define GPS_PRECISION_MIN_ADDRESS 0x02
#define GPS_PRECISION_MIN_SIZE 1
#define GPS_PRECISION_MIN_DEFAULT 5

#define GPS_WRITE_DELAY_ADDRESS 0x03
#define GPS_WRITE_DELAY_SIZE 1
#define GPS_WRITE_DELAY_DEFAULT 10

#define GPS_FIX_MAX_ADDRESS 0x04
#define GPS_FIX_MAX_SIZE 1
#define GPS_FIX_MAX_DEFAULT 20


struct ConfigData
{
  public:
    virtual uint16_t value() = 0;
    virtual void setDefault() = 0;

  protected:
    uint16_t readValueFromMemory(uint16_t address, byte size);
    void writeValueToMemory(uint16_t address, uint16_t data, byte size);
};

struct FileCounter : public ConfigData
{
  public:
    uint16_t value() { return readValueFromMemory(FILE_COUNTER_ADDRESS, FILE_COUNTER_SIZE); }
    void setDefault() { writeValueToMemory(FILE_COUNTER_ADDRESS, FILE_COUNTER_DEFAULT, FILE_COUNTER_SIZE); }
    FileCounter operator++(int);

  private:
    void increaseCounterValue() { writeValueToMemory(FILE_COUNTER_ADDRESS, value() + 1, FILE_COUNTER_SIZE); }
};

struct GPSPrecision : public ConfigData
{
  public:
    uint16_t value() { return readValueFromMemory(GPS_PRECISION_MIN_ADDRESS, GPS_PRECISION_MIN_SIZE); }
    void setDefault() { writeValueToMemory(GPS_PRECISION_MIN_ADDRESS, GPS_PRECISION_MIN_DEFAULT, GPS_PRECISION_MIN_SIZE); }
};

struct GPSWriteDelay : public ConfigData
{
  public:
    uint16_t value() { return readValueFromMemory(GPS_WRITE_DELAY_ADDRESS, GPS_WRITE_DELAY_SIZE); }
    void setDefault() { writeValueToMemory(GPS_WRITE_DELAY_ADDRESS, GPS_WRITE_DELAY_DEFAULT, GPS_WRITE_DELAY_SIZE); }
};

struct GPSFixTimeout : public ConfigData
{
  public:
    uint16_t value() { return readValueFromMemory(GPS_FIX_MAX_ADDRESS, GPS_FIX_MAX_SIZE); }
    void setDefault() { writeValueToMemory(GPS_FIX_MAX_ADDRESS, GPS_FIX_MAX_DEFAULT, GPS_FIX_MAX_SIZE); }
};

class ConfigurationDataRepository
{
  public:
    FileCounter fileCounter;
    GPSPrecision gpsPrecision;
    GPSWriteDelay gpsWriteDelay;
    GPSFixTimeout gpsFixTimeout;
};
#endif