#ifndef SDDATAREPOSITORY_H
#define SDDATAREPOSITORY_H

#include "Arduino.h"
#include "GPSDataModel.h"
#include "SDFileService.h"

class SDDataRepository
{
	public:
		SDDataRepository(SDFileService* fileService) : fileService(fileService) { }
		void createNewTrack(GPSPoint point);
		void writeNewTrackSegment();
		void writeNewWaypoint(GPSWaypoint waypoint);
		void writeNewPoint(GPSPoint point);
		
	private:
		void checkFile();
		void writePointBody(GPSPoint point);
		SDFileService* fileService;
};

#endif