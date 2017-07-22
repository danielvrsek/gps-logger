#ifndef GPSHANDLER_H
#define GPSHANDLER_H

#include "Arduino.h"
#include "GPSDataHandler.h"
#include "ErrorHandler.h"
#include "StatusLedHandler.h"
#include "../tiny-gps/TinyGPS++.h"

// Receive pin for SoftwareSerial
#define GPS_RX_PIN 5
// Transmit pin for SoftwareSerial
#define GPS_TX_PIN 6
// Pin, where FIX led is connected
#define FIX_LED 5

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

// Fix led blinks while gps is not fixed
#define FIX_LED_DELAY 300

class GPSHandler
{
  public:
    void loop();
	void begin();
   
  private:
    bool isGPSReady();
    bool isWriteTimerReady();
    void displayGPSPoint(GPSPoint gpsPoint);
    GPSPoint getCurrentPoint();
    GPSPosition getCurrentPosition();
    GPSDate getCurrentDate();
    GPSTime getCurrentTime();
    char* getCurrentUtcTime();
    void fixLedHandle(); 
    void functionButtonHandle();

    void statusLed_Handler();
    void fixLed_Handler();
    void newTrackingPressed_Handler();

    TinyGPSPlus gps;
    GPSDataHandler dataHandler;
    byte gpsPrecision, gpsWriteDelay, gpsFixTimeout;
    unsigned long writeTimer, fixLedTimer, gpsFixTimer, functionButtonTimer;
    bool functionButtonPressed, trackIndicator, waypointIndicator;
    bool gpsFixed = false;
};

#endif
