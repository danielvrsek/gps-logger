#include "GPSHandler.h"


void GPSHandler::begin()
{
	writeTimer = fixLedTimer = gpsFixTimer = functionButtonTimer = 0;
	functionButtonPressed = trackIndicator = waypointIndicator = false;
Serial.print("freeMemory()=");
	Configuration config;

/*	config.gpsPrecision.setDefault();
	config.gpsWriteDelay.setDefault();
	config.gpsFixTimeout.setDefault();*/
  
	gpsPrecision = config.gpsPrecision.value();
	gpsWriteDelay = config.gpsWriteDelay.value();
	gpsFixTimeout = config.gpsFixTimeout.value();

	Serial.println(gpsPrecision);
	Serial.println(gpsWriteDelay);
	Serial.println(gpsFixTimeout);
  
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

	StatusLedHandler::Instance()->handle();
	functionButtonHandle();
	fixLedHandle();
  
	if (isGPSReady() && isWriteTimerReady()) 
	{
		dataHandler.writeNewPoint(getCurrentPoint());
	}
}

GPSPoint GPSHandler::getCurrentPoint()
{
	GPSPoint gpsPoint;
	gpsPoint.position = getCurrentPosition();
	gpsPoint.speed = gps.speed.kmph();
	//gpsPoint.utcTime = getCurrentUtcTime();
	
	return gpsPoint;
}

bool GPSHandler::isWriteTimerReady()
{
	if (millis() - writeTimer > gpsWriteDelay * 1000)
	{      
		writeTimer = millis();

		return true;
	}

	return false;
}

void GPSHandler::functionButtonHandle()
{
	bool state = digitalRead(FUNCTION_BUTTON_PIN);
  
	if (functionButtonPressed)
	{
		unsigned long delay = millis() - functionButtonTimer;

		if (delay > NEW_TRACKING_SET_DELAY)
		{
			if (state && !trackIndicator)
			{
				StatusLedHandler::Instance()->blink(2, NEW_TRACKING_LED_DELAY);
				trackIndicator = true;
			}
			else if (!state)
				dataHandler.createNewTrack(getCurrentPoint());
		}
		else if (delay > NEW_POI_SET_DELAY)
		{
			if (state && !waypointIndicator)
			{
				StatusLedHandler::Instance()->blink(1, NEW_POI_LED_DELAY);
				waypointIndicator = true;
			}
			else if (!state)
			{
				GPSWaypoint* pWaypoint = &getCurrentPoint();
				(*pWaypoint).waypointType = WaypointType::Poi;
		
				dataHandler.writeNewWaypoint(*pWaypoint);
			}
		}

		if (!state)
			functionButtonPressed = waypointIndicator = trackIndicator = false;      
	}
  
	if(!functionButtonPressed && state)
	{ 
		functionButtonTimer = millis();
		functionButtonPressed = true;
	}
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

GPSPosition GPSHandler::getCurrentPosition()
{
	GPSPosition position;
  
	position.lat = gps.location.lat();
	position.lng = gps.location.lng();
	position.alt = (uint16_t)gps.altitude.meters();

	return position;
}

GPSDate GPSHandler::getCurrentDate()
{
	GPSDate date;
  
	date.year = gps.date.year();
	date.month = gps.date.month();
	date.day = gps.date.day();

	return date;
}

GPSTime GPSHandler::getCurrentTime()
{
	GPSTime time;

	time.hour = gps.time.hour();
	time.minute = gps.time.minute();
	time.second = gps.time.second();

	return time;
}

char* GPSHandler::getCurrentUtcTime()
{
	GPSTime time = getCurrentTime();
}
