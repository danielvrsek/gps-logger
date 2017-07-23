#include "GPSHandler.h"

int freeRam();

void GPSHandler::begin()
{
	writeTimer = fixLedTimer = gpsFixTimer = 0;
	
	functionButtonHandler = new FunctionButtonHandler(this);
	statusLedHandler = StatusLedHandler::Instance();
	
	ConfigurationDataRepository config;

	config.gpsPrecision.setDefault();
	config.gpsWriteDelay.setDefault();
	config.gpsFixTimeout.setDefault();
  
	gpsPrecision = config.gpsPrecision.value();
	gpsWriteDelay = config.gpsWriteDelay.value();
	gpsFixTimeout = config.gpsFixTimeout.value();
    
	Serial.println(freeRam());
	
	pinMode(FIX_LED, OUTPUT);
	digitalWrite(FIX_LED, LOW);
}

void GPSHandler::loop()
{
	while (Serial.available() > 0)
	{
		char c = Serial.read();
		Serial.print(c);
		gps.encode(c);
	}

	statusLedHandler->loop();
	functionButtonHandler->loop();
	fixLedHandle();
  
	if (isGPSReady() && isTimeToWrite()) 
	{
		GPSDataRepository gpsRepository = GPSDataRepository(&gps);
		SDDataRepository sdRepository = SDDataRepository(SDFileService::Instance());
		
		sdRepository.writeNewPoint(gpsRepository.getCurrentPoint());
	}
}

bool GPSHandler::isGPSReady()
{
	if (gps.location.age() < 2000 && gps.hdop.value() / 100 <= gpsPrecision)
	{
		if (!gpsFixed) digitalWrite(FIX_LED, HIGH);
		gpsFixTimer = millis();
        
		return gpsFixed = true;    
	}	
  
	if (gpsFixed && millis() - gpsFixTimer < gpsFixTimeout * 1000)
	{
		gpsFixed = true;
		return false;
	}
  
	return gpsFixed = false;
}

bool GPSHandler::isTimeToWrite()
{
	if (millis() - writeTimer > gpsWriteDelay * 1000)
	{      
		writeTimer = millis();

		return true;
	}

	return false;
}

void GPSHandler::fixLedHandle()
{
	if (gpsFixed && isGPSReady()) return;
  
	if (!gpsFixed && millis() - fixLedTimer > FIX_LED_DELAY)
	{
		digitalWrite(FIX_LED, !digitalRead(FIX_LED));
		fixLedTimer = millis();
	}
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
	GPSDataRepository gpsRepository = GPSDataRepository(&gps);
	SDDataRepository sdRepository = SDDataRepository(SDFileService::Instance());
	
	GPSPoint point = gpsRepository.getCurrentPoint();
	GPSWaypoint* p_waypoint = (GPSWaypoint*)&point;
	
	p_waypoint->waypointType = WaypointType::Poi;

	sdRepository.writeNewWaypoint(*p_waypoint);
}

void GPSHandler::onNewTrackingPressed()
{
	GPSDataRepository gpsRepository = GPSDataRepository(&gps);
	SDDataRepository sdRepository = SDDataRepository(SDFileService::Instance());
	
	sdRepository.createNewTrack(gpsRepository.getCurrentPoint());
}

GPSHandler::~GPSHandler()
{
	delete functionButtonHandler;
}