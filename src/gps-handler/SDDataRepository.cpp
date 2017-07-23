#include "SDDataRepository.h"

const char dataDivider = ',';

void SDDataRepository::createNewTrack(GPSPoint point)
{
	Serial.println(F("Creating new track..."));

	GPSWaypoint* p_Waypoint = (GPSWaypoint*)&point;

	if (fileService->isOpen())
	{
		(*p_Waypoint).waypointType = WaypointType::End;
		writeNewWaypoint(*p_Waypoint);

		fileService->close();
	}

	fileService->create();

	(*p_Waypoint).waypointType = WaypointType::Start;
	writeNewWaypoint(*p_Waypoint);
	writeNewTrackSegment();
}

void SDDataRepository::writeNewTrackSegment()
{
	Serial.println(F("Writing new track segment..."));

	checkFile();

	fileService->file.println(DataType::TrackSegment);
	fileService->file.flush();
}

void SDDataRepository::writeNewWaypoint(GPSWaypoint waypoint)
{
	Serial.println(F("Writing new waypoint..."));

	checkFile();

	fileService->file.print(DataType::Waypoint);
	fileService->file.print(dataDivider);
	fileService->file.print(waypoint.waypointType);
	fileService->file.print(dataDivider);
	writePointBody((GPSPoint)waypoint);
	fileService->file.flush();
}

void SDDataRepository::writeNewPoint(GPSPoint point)
{
	Serial.println(F("Writing new point..."));

	checkFile();

	fileService->file.print(DataType::TrackPoint);
	fileService->file.print(dataDivider);
	writePointBody(point);
	fileService->file.flush();
}

void SDDataRepository::writePointBody(GPSPoint point)
{
	fileService->file.print(point.position.lat, 7);
	fileService->file.print(dataDivider);
	fileService->file.print(point.position.lng, 7);
	fileService->file.print(dataDivider);
	fileService->file.print(point.position.alt);
	fileService->file.print(dataDivider);
	fileService->file.println(point.speed);
}

void SDDataRepository::checkFile()
{
	if (!fileService->isOpen())
	{
		fileService->open();
		writeNewTrackSegment();
	}
}
