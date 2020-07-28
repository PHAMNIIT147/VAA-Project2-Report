#ifndef FIREBASE_H
#define FIREBASE_H

#include <Arduino.h>
#include <FirebaseESP8266.h>
#include <SensorDHT.h>

#define FIREBASE_HOST "iot-data-hardware.firebaseio.com"
#define FIREBASE_AUTH "Cx10R8oWZG8O3njWSveXgDZC0FsNUKaEuPDh3zaO"

class ManagerFirebase
{
private:
  String mHost;
  String mAuth;
  String mPath;

public:
  ManagerFirebase(String host, String auth);
  ManagerFirebase();
  ~ManagerFirebase();

  void init();

  void setPath(String path);

  String getPath();

  void updateDataRealTime(uint8_t data);

  void uploadDatabase();
};
#endif //FIREBASE_H