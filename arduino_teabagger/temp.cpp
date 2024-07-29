#include "temp.h"
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

unsigned long tempTime;
const int measruementInterval = 5000;
float lastTemp;
bool isIncreasing = true;

void setupTemp(){
  sensors.begin();
  tempTime = millis();
  lastTemp = getTemp();
}

float getTemp(){
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

bool tempIncreasing(){
  if (millis() - tempTime >= measruementInterval) {
    if (lastTemp < getTemp()) {
      isIncreasing = true;
    } else {
      isIncreasing = false;
    }
    lastTemp = getTemp();
  }
  return isIncreasing;
}

