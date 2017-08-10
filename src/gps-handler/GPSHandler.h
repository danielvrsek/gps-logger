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
#include "../display-handler/DisplayHandler.h"

#include "../neo-swserial/NeoSWSerial.h"
#include "../neo-gps/NMEAGPS.h"

// Receive pin for SoftwareSerial
#define GPS_RX_PIN 7
// Transmit pin for SoftwareSerial
#define GPS_TX_PIN 2

// Fix led blinks while gps is not fixed
#define FIX_LED_DELAY 300

class GPSHandler
{
	public:
		GPSHandler() { }
		GPSHandler(DisplayHandler* display) : display(display) { }
		~GPSHandler();
		
		void loop();
		void begin();
			
		void onNewTrackingPressed();
		void onNewPoiPressed();
   
	private:
		void updateDisplay();
		void changeGpsIconState(bool state);
		bool isTimeToWrite();
		void displayGPSPoint(GPSPoint gpsPoint);

		GPSDataRepository* gpsRepository;
		SDDataRepository* sdRepository;
		FunctionButtonHandler* functionButtonHandler;
		StatusLedHandler* statusLedHandler;
		DisplayHandler* display;
		NMEAGPS gps;
		unsigned long writeTimer = 0, displayUpdateTimer = 0;
		bool gpsIconState = true, displayRequiresDelete = false;
};

#endif
