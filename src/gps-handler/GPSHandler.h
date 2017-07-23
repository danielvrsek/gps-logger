class GPSHandler;

#ifndef GPSHANDLER_H
#define GPSHANDLER_H

#include "Arduino.h"
#include "ErrorHandler.h"
#include "StatusLedHandler.h"
#include "FunctionButtonHandler.h"
#include "GPSDataModel.h"
#include "GPSDataRepository.h"
#include "SDDataRepository.h"
#include "SDFileService.h"
#include "ConfigurationDataRepository.h"

// Receive pin for SoftwareSerial
#define GPS_RX_PIN 5
// Transmit pin for SoftwareSerial
#define GPS_TX_PIN 6
// Pin, where FIX led is connected
#define FIX_LED 5

// Fix led blinks while gps is not fixed
#define FIX_LED_DELAY 300

class GPSHandler
{
	public:
		~GPSHandler();
		
		void loop();
		void begin();
	
		void onNewTrackingPressed();
		void onNewPoiPressed();
   
	private:
		bool isGPSReady();
		bool isTimeToWrite();
		void displayGPSPoint(GPSPoint gpsPoint);
		void fixLedHandle();

		FunctionButtonHandler* functionButtonHandler;
		StatusLedHandler* statusLedHandler;
		TinyGPSPlus gps;
		byte gpsPrecision, gpsWriteDelay, gpsFixTimeout;
		unsigned long writeTimer, fixLedTimer, gpsFixTimer;
		bool gpsFixed = false;
};

#endif
