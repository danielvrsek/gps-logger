#ifndef STATUSLEDHANDLER_H
#define STATUSLEDHANDLER_H

#include "Arduino.h"

#define STATUS_LED 4

class StatusLedHandler
{
  public:
    static StatusLedHandler* Instance();
    void loop();
    void blink(byte amount, uint16_t delay);
    void blinkError(byte amount);
  private:
    StatusLedHandler();
    unsigned long mTimer;
    uint16_t mAmount;
    uint16_t mDelay;

    static StatusLedHandler* p_instance;
};
#endif