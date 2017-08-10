#include "GPSDataRepository.h"


GPSPoint GPSDataRepository::getCurrentPoint()
{
	GPSPoint gpsPoint;
	
	gpsPoint.position = getCurrentPosition();
	gpsPoint.speed = fix_data.speed_kph();
	//gpsPoint.utcTime = getCurrentUtcTime();
	
	return gpsPoint;
}

GPSPosition GPSDataRepository::getCurrentPosition()
{
	GPSPosition position;
  
	position.lat = fix_data.latitude();
	position.lng = fix_data.longitude();
	position.alt = fix_data.alt.whole;

	return position;
}

GPSDate GPSDataRepository::getCurrentDate()
{
	GPSDate date;
  
	date.year = fix_data.dateTime.year;
	date.month = fix_data.dateTime.month;
	date.day = fix_data.dateTime.date;

	return date;
}

GPSTime GPSDataRepository::getCurrentTime()
{
	GPSTime time;

	time.hour = fix_data.dateTime.hours;
	time.minute = fix_data.dateTime.minutes;
	time.second = fix_data.dateTime.seconds;

	return time;
}

void GPSDataRepository::updateGpsFix(gps_fix fix_data)
{
	this->fix_data = fix_data;
	
	NeoGPS::Location_t location = NeoGPS::Location_t( _lastPosition.lat, _lastPosition.lng );
	_traveledDistance += fix_data.location.DistanceKm( location );
	
	_lastPosition = getCurrentPosition();
	timeWhenDataLastUpdated = millis();
}

void GPSDataRepository::updateGpsStatus()
{
	// TODO updated??
	if ( fix_data.valid.location && fix_data.valid.speed && fix_data.valid.altitude )
	{
		_gpsFixed = true;
	}
  
	// TODO gpsFixTimeout
	if (millis() - timeWhenDataLastUpdated < 5 * 1000)
	{
		_gpsFixed = true;
	}
  
	_gpsFixed = false;
}