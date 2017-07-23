/*enum DataType;
enum WaypointType;
struct GPSDate;
struct GPSTime;
struct GPSPosition;
struct GPSData;
struct GPSPoint : public GPSData;
struct GPSWaypoint : public GPSPoint;*/

#ifndef GPSDATAMODEL_H
#define GPSDATAMODEL_H

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

struct GPSPoint : public GPSData
{
  GPSPosition position;
  double speed;
  char *utcTime;
};

struct GPSWaypoint : public GPSPoint
{
  byte waypointType;
};

#endif