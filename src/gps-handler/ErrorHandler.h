#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include "StatusLedHandler.h"

enum Error
{
  SDCARD_ERROR = 5,
  EEPROM_ERROR = 6
};

class ErrorHandler
{
  public:
    static void handleError(Error err)
    {
      Serial.println("Error");
      while (true)
      {
        StatusLedHandler::Instance()->blinkError(err);
        delay(1000);
      }
    }
};

#endif
