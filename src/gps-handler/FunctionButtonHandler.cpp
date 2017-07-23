#include "FunctionButtonHandler.h"

FunctionButtonHandler::FunctionButtonHandler(GPSHandler* p_gpsHandler)
{
	// Initializing values
	this->p_gpsHandler = p_gpsHandler;
	
	isPressed = isHeld = false;
	newTrackingIndicated = newPoiIndicated = false;
	buttonTimer = 0;
	
	// Setting pin mode for function button to INPUT
	pinMode(FUNCTION_BUTTON_PIN, INPUT);
}

void FunctionButtonHandler::loop()
{
	isPressed = digitalRead(FUNCTION_BUTTON_PIN);
  
	// This is true, when the button is held for some period of time
	if (isHeld)
	{
		functionButtonHeld();
	}
	// This is true, when the button was pressed, but we weren't counting time yet
	else if(isPressed && !isHeld)
	{ 
		// Start counting for how long user holds the button
		buttonTimer = millis();
		isHeld = true;
	}
}

void FunctionButtonHandler::functionButtonHeld()
{
	// Get the delay between now and when the user pressed the button
	// Simply said, this is the time, for how long user holds the button
	unsigned long delay = millis() - buttonTimer;
	
	// If the delay is longer than ... then ...
	// Note, that in order for this to work properly, functions with higher required delay need to be stated first
	if (delay > NEW_TRACKING_SET_DELAY)
	{
		newTrackingDelayReached();
	}
	else if (delay > NEW_POI_SET_DELAY)
	{
		newPoiDelayReached();
	}
	
	// This is true, when button state is HELD, but the button is not pressed anymore
	if (!isPressed)
	{
		isHeld = newPoiIndicated = newTrackingIndicated = false;	  
	}
}

void FunctionButtonHandler::newTrackingDelayReached()
{
	// This is true, when the button is still pressed, but we hadn't indicated new tracking yet
	if (isPressed && !newTrackingIndicated)
	{
		StatusLedHandler::Instance()->blink(2, NEW_TRACKING_LED_DELAY);
		newTrackingIndicated = true;
	}
	// This is true, when the delay needed for triggering method was reached and the button is not pressed anymore
	else if (!isPressed)
	{
		// Call method pointer
		p_gpsHandler->onNewTrackingPressed();
	}
}

void FunctionButtonHandler::newPoiDelayReached()
{
	// This is true, when the button is still pressed, but we hadn't indicated new poi yet
	if (isPressed && !newPoiIndicated)
	{
		StatusLedHandler::Instance()->blink(1, NEW_POI_LED_DELAY);
		newPoiIndicated = true;
	}
	// This is true, when the delay needed for triggering method was reached and the button is not pressed anymore
	else if (!isPressed)
	{
		// Call method pointer
		p_gpsHandler->onNewPoiPressed();
	}
}