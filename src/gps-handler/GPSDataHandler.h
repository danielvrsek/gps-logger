#ifndef GPSDATAHANDLER_H
#define GPSDATAHANDLER_H

#include "../eeprom/EEPROM_I2C.h"
#include "ErrorHandler.h"
#include "Configuration.h"
#include <SPI.h>
#include <SD.h>

#define SDCARD_SS_PIN 9

#define FILE_NAME_SIZE 8

#define FILE_PREFIX "TRCK"
#define FILE_PREFIX_SIZE 4

#define FILE_EXTENSION "DAT"
#define FILE_EXTENSION_SIZE 3

#define FILE_DIVIDER ','


enum DataType 
{
  Waypoint,
  TrackSegment,
  TrackPoint
};

enum WaypointType
{
  Start,
  End,
  Poi
};

struct GPSDate
{
  uint16_t year;
  uint8_t month;
  uint8_t day;
};

struct GPSTime
{
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
};

struct GPSPosition
{
  double lat;
  double lng;
  uint16_t alt;
};

struct GPSData
{
  byte dataType;
};

struct GPSPoint : GPSData
{
  GPSPosition position;
  double speed;
  char *utcTime;
};

struct GPSWaypoint : GPSPoint
{
  byte waypointType;
};

class GPSDataHandler
{
  public:
    GPSDataHandler();
    void createNewTrack(GPSPoint point);
    void writeNewTrackSegment();
    void writeNewPoint(GPSPoint pt);
    void writeNewWaypoint(GPSWaypoint wp);
    void writePointBody(GPSPoint point);
    bool readNext(GPSData *data);

  private:
    void getFilename(uint16_t counter, char* filename);
    void openFile();
    void checkFile();

    File gpsFile;
    FileCounter fileCounter;
};
#endif
