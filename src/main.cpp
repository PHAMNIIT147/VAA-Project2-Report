#include <Arduino.h>
#include "header.h"

/* main */
void setup()
{
  configPin();
  managerConnect();
  Serial.println(F("Start ESP8266"));
}

void loop()
{
  firebase.uploadDatabase();
}

/* function */
void configPin()
{
  Serial.begin(9600);
}

void managerConnect()
{
  wifiManager.autoConnect("ZiPi Config WiFi", "301681559");
  firebase.init();
  sensor.init();
}
