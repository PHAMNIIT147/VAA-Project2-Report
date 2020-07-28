#ifndef HEADER_H
#define HEADER_H

#include <Arduino.h>
#include <WiFiManager.h>
#include "ManagerFirebase.h"
#include "SensorDHT.h"

WiFiManager wifiManager;
ManagerFirebase firebase;
SensorDHT sensor;

//configuration function for project
void configPin();

void managerConnect();

#endif //HEADER_H