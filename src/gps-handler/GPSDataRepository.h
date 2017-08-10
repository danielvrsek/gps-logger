#ifndef GPSDATAREPOSITORY_H
#define GPSDATAREPOSITORY_H

#include "../neo-gps/NMEAGPS.h"
#include "../neo-gps/Location.h"
#include "GPSDataModel.h"

class GPSDataRepository
{
	public:	
		uint8_t getCurrentSpeed();
		GPSPoint getCurrentPoint();
		GPSPosition getCurrentPosition();
		GPSDate getCurrentDate();
		GPSTime getCurrentTime();
		void updateGpsFix(gps_fix fix_data);
		void updateGpsStatus();
		bool isGpsFixed() { return _gpsFixed; }
		double getTraveledDistanceL() { return _traveledDistance; }
		uint32_t getTraveledDistance() { return _traveledDistance * 100; }
		
	private:
		gps_fix fix_data;
		GPSPosition _lastPosition;
		double _traveledDistance = 0;
		byte gpsPrecision, gpsWriteDelay, gpsFixTimeout;
		unsigned long timeWhenDataLastUpdated = 0;
		bool _gpsFixed = false;
};

#endif
