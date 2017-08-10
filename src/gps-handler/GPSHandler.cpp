#include "GPSHandler.h"

NeoSWSerial gpsSerial(GPS_RX_PIN, GPS_TX_PIN);

void GPSHandler::begin()
{
	gpsSerial.begin(9600);
	
	if (!display)
	{
		display = new DisplayHandler;
		display->begin();
		displayRequiresDelete = true;
	}
	
	gpsRepository = new GPSDataRepository();
	sdRepository = new SDDataRepository(SDFileService::Instance());
	functionButtonHandler = new FunctionButtonHandler(this);
	statusLedHandler = StatusLedHandler::Instance();
}

void GPSHandler::loop()
{
	while (gps.available(gpsSerial))
	{
		gps_fix fix_data = gps.read();
		gpsRepository->updateGpsFix(fix_data);
		Serial.println("Updated");
	}
	gpsRepository->updateGpsStatus();

	statusLedHandler->loop();
	functionButtonHandler->loop();
	
	if (millis() - displayUpdateTimer > 1000)
	{
		displayUpdateTimer = millis();
		updateDisplay();
	}
  
	/*if (gpsRepository->isGpsFixed() && isTimeToWrite()) 
	{
		sdRepository->writeNewPoint(gpsRepository->getCurrentPoint());
	}*/
}

void GPSHandler::updateDisplay()
{
	bool gpsFixed = gpsRepository->isGpsFixed();
	
	GPSPoint point = gpsRepository->getCurrentPoint();
		
	display->drawSpeed((uint8_t)point.speed);
	display->drawData(gpsRepository->getTraveledDistance(), 2);
	
	if (gpsFixed && !gpsIconState)
		changeGpsIconState(true);
	else if (!gpsFixed && gpsIconState)
		changeGpsIconState(false);
	else if (!gpsFixed && !gpsIconState)
		changeGpsIconState(true);
}

void GPSHandler::changeGpsIconState(bool state)
{	
	if (state)
	{
		display->drawGpsIcon();
		gpsIconState = true;
	}
	else
	{
		display->clearGpsIcon();
		gpsIconState = false;
	}
}

bool GPSHandler::isTimeToWrite()
{
	if (millis() - writeTimer > 5 * 1000)
	{      
		writeTimer = millis();

		return true;
	}

	return false;
}

void GPSHandler::displayGPSPoint(GPSPoint gpsPoint)
{
	/*if (gpsPoint.checkSumChecks(GPSDataBase::countDataCheckSum(gpsPoint))) { Serial.println("Invalid"); }
	Serial.print(gpsData.checkSum, BIN); Serial.print(" : ");
	//Serial.println(GPSDataBase::countDataCheckSum(gpsData), BIN);
	Serial.print("LAT: "); Serial.print(gpsData.position.lat, 6);
	Serial.print(", LONG: "); Serial.print(gpsData.position.lng, 6);
	Serial.print(", ALT: "); Serial.println((uint16_t)gpsData.position.alt);
	Serial.print(", HOUR: "); Serial.println(gpsData.time.hour);
	Serial.print(", MINUTE: "); Serial.println(gpsData.time.minute);
	Serial.print(", SECOND: "); Serial.println(gpsData.time.second);*/
}

void GPSHandler::onNewPoiPressed()
{
	GPSPoint point = gpsRepository->getCurrentPoint();
	GPSWaypoint* p_waypoint = (GPSWaypoint*)&point;
	
	p_waypoint->waypointType = WaypointType::Poi;

	sdRepository->writeNewWaypoint(*p_waypoint);
}

void GPSHandler::onNewTrackingPressed()
{
	sdRepository->createNewTrack(gpsRepository->getCurrentPoint());
}

GPSHandler::~GPSHandler()
{
	delete functionButtonHandler;
	delete gpsRepository;
	delete sdRepository;
	
	if (displayRequiresDelete)
		delete display;
}