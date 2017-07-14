#include "GPSDataHandler.h"

GPSDataHandler::GPSDataHandler()
{  
  Configuration config;
  fileCounter = config.fileCounter;
  //fileCounter.setDefault();

  char filename[FILE_NAME_SIZE + 1 + FILE_EXTENSION_SIZE];
  getFilename(fileCounter.value(), filename);

  Serial.println(filename);
  
  if (!SD.begin(SDCARD_SS_PIN)) 
    ErrorHandler::handleError(Error::SDCARD_ERROR);
}

void GPSDataHandler::openFile()
{
  Serial.println(F("Opening file..."));
  char filename[FILE_NAME_SIZE + 1 + FILE_EXTENSION_SIZE];
  getFilename(fileCounter.value(), filename);
  
  gpsFile = SD.open(filename, FILE_WRITE);

  if (!gpsFile)
    ErrorHandler::handleError(Error::SDCARD_ERROR);
}

void GPSDataHandler::createNewTrack(GPSPoint point)
{  
  Serial.println(F("Creating new track..."));

  GPSWaypoint* pWaypoint = &point;
  
  if (gpsFile)
  {
    (*pWaypoint).waypointType = WaypointType::End;
    writeNewWaypoint(*pWaypoint);
    
    gpsFile.close();
  }

  fileCounter++;
  openFile();

  (*pWaypoint).waypointType = WaypointType::Start;
  writeNewWaypoint(*pWaypoint);
  writeNewTrackSegment();
}

void GPSDataHandler::checkFile()
{
  if (!gpsFile)
  {
    openFile();
    writeNewTrackSegment();
  }
}

void GPSDataHandler::writeNewTrackSegment()
{
  Serial.println(F("Writing new track segment..."));
  
  checkFile();
  
  gpsFile.println(DataType::TrackSegment);
  gpsFile.flush();
}

void GPSDataHandler::writeNewPoint(GPSPoint point)
{
  Serial.println(F("Writing new point..."));
  char divider = FILE_DIVIDER;

  checkFile();
  
  gpsFile.print(DataType::TrackPoint);
  gpsFile.print(divider);
  writePointBody(point);
  gpsFile.flush();
}

void GPSDataHandler::writePointBody(GPSPoint point)
{
  char divider = FILE_DIVIDER;
  
  gpsFile.print(point.position.lat, 7);
  gpsFile.print(divider);
  gpsFile.print(point.position.lng, 7);
  gpsFile.print(divider);
  gpsFile.print(point.position.alt);
  gpsFile.print(divider);
  gpsFile.println(point.speed);
}

void GPSDataHandler::writeNewWaypoint(GPSWaypoint waypoint)
{
  Serial.println(F("Writing new waypoint..."));
  char divider = FILE_DIVIDER;

  checkFile();
  
  gpsFile.print(DataType::Waypoint);
  gpsFile.print(divider);
  gpsFile.print(waypoint.waypointType);
  gpsFile.print(divider);
  writePointBody((GPSPoint)waypoint);
  gpsFile.flush();
}

void GPSDataHandler::getFilename(uint16_t counter, char* filename)
{
  byte index = 0;
  char* filePrefix = FILE_PREFIX;
  char* extension = FILE_EXTENSION;

  for (byte i = 0; i < FILE_PREFIX_SIZE; i++)
    filename[index++] = filePrefix[i];

  filename[index++] = (counter / 1000) + 48;
  filename[index++] = (counter % 1000 / 100) + 48;
  filename[index++] = (counter % 100 / 10) + 48;
  filename[index++] = (counter % 10) + 48;
  filename[index++] = '.';

  for (byte i = 0; i < FILE_EXTENSION_SIZE; i++)
    filename[index++] = extension[i];

  filename[index] = '\0';
}
