#ifndef GPSDATAREPOSITORY_H
#define GPSDATAREPOSITORY_H

#include "../tiny-gps/TinyGPS++.h"
#include "GPSDataModel.h"

class GPSDataRepository
{
	public:
		GPSDataRepository(TinyGPSPlus* p_gps) : gps(p_gps) { }
	
		uint8_t getCurrentSpeed();
		GPSPoint getCurrentPoint();
		GPSPosition getCurrentPosition();
		GPSDate getCurrentDate();
		GPSTime getCurrentTime();
		
	private:
		TinyGPSPlus* gps;
};

#endif
