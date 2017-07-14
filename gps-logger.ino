#include "src/gps-handler/GPSHandler.h"
#include <MemoryFree.h>

#include <SoftwareSerial.h>


SoftwareSerial gpsSerial(5, 6);

GPSHandler* p_gpsHandler;

void setup() {
  Serial.begin(9600);
  
  p_gpsHandler = new GPSHandler();
  Serial.print("freeMemory()=");
  Serial.println(freeMemory());
}

void loop() {
  p_gpsHandler->loop();
}
