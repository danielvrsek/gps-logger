class FunctionButtonHandler;

#ifndef FUNCTIONBUTTONHANDLER_H
#define FUNCTIONBUTTONHANDLER_H

#include "Arduino.h"
#include "StatusLedHandler.h"
#include "GPSHandler.h"

// Time that button needs to be pressed to start a new tracking
#define NEW_TRACKING_SET_DELAY 3000
// Time that LED is on after the new tracking started
#define NEW_TRACKING_LED_DELAY 250

#define WRITE_CONFIRM_LED_DELAY 200

// Time that button needs to be pressed to save a POI
#define NEW_POI_SET_DELAY 350
// Time that LED is on after the POI was saved
#define NEW_POI_LED_DELAY 250

// Pin, where a function button is connected
#define FUNCTION_BUTTON_PIN 3

class FunctionButtonHandler
{
	public:
		// Constructor
		FunctionButtonHandler(GPSHandler* p_gpsHandler);
		// Loop
		void loop();
	
	private:
		// These methods are called when time required for activating any of these functions was reached
		void newPoiDelayReached();
		void newTrackingDelayReached();
		// This method is called when button is pressed for some period of time
		void functionButtonHeld();
		
		GPSHandler* p_gpsHandler;
		
		bool isPressed, isHeld;
		bool newTrackingIndicated, newPoiIndicated;
		unsigned long buttonTimer;
};

#endif