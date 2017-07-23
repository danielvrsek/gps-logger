#include "StatusLedHandler.h"

StatusLedHandler* StatusLedHandler::p_instance = 0;

StatusLedHandler::StatusLedHandler() :
    mTimer(0)
  , mAmount(0)
  , mDelay(0)
{
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, LOW);
}

void StatusLedHandler::loop()
{  
  if (mAmount == 0) return;

  if (millis() - mTimer > mDelay)
  {
    digitalWrite(STATUS_LED, !digitalRead(STATUS_LED));
    mTimer = millis();
    mAmount--;
  }
}

void StatusLedHandler::blink(byte amount, uint16_t delay)
{
  mAmount = amount * 2;
  mDelay = delay;
}

void StatusLedHandler::blinkError(byte amount)
{
  blink(amount, 350);
  
  while(mAmount)
  {
    loop();
  }
}

StatusLedHandler* StatusLedHandler::Instance()
{
  if (!p_instance)
  {
    p_instance = new StatusLedHandler;
  }

  return p_instance;
}