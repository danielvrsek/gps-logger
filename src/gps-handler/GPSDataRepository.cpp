#include "GPSDataRepository.h"


GPSPoint GPSDataRepository::getCurrentPoint()
{
	GPSPoint gpsPoint;
	gpsPoint.position = getCurrentPosition();
	gpsPoint.speed = gps->speed.kmph();
	//gpsPoint.utcTime = getCurrentUtcTime();
	
	return gpsPoint;
}

GPSPosition GPSDataRepository::getCurrentPosition()
{
	GPSPosition position;
  
	position.lat = gps->location.lat();
	position.lng = gps->location.lng();
	position.alt = (uint16_t)gps->altitude.meters();

	return position;
}

GPSDate GPSDataRepository::getCurrentDate()
{
	GPSDate date;
  
	date.year = gps->date.year();
	date.month = gps->date.month();
	date.day = gps->date.day();

	return date;
}

GPSTime GPSDataRepository::getCurrentTime()
{
	GPSTime time;

	time.hour = gps->time.hour();
	time.minute = gps->time.minute();
	time.second = gps->time.second();

	return time;
}