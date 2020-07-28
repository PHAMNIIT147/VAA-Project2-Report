#include "ManagerFirebase.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

FirebaseData fData;
FirebaseJson json;

SensorDHT mData;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "vn.pool.ntp.org", 25200, 60000);

ManagerFirebase::ManagerFirebase(String host, String auth) : mHost(host), mAuth(auth) {}

ManagerFirebase::ManagerFirebase() : mHost(FIREBASE_HOST), mAuth(FIREBASE_AUTH) {}

ManagerFirebase::~ManagerFirebase()
{
  Serial.println("free memory");
}

void ManagerFirebase::init()
{
  Firebase.begin(mHost, mAuth);
  timeClient.begin();
}

void ManagerFirebase::setPath(String path)
{
  this->mPath = path;
}

String ManagerFirebase::getPath()
{
  return mPath;
}

void ManagerFirebase::updateDataRealTime(uint8_t data)
{

  if (!Firebase.setInt(fData, getPath(), data))
  {
    Serial.println("Update failure!");
  }
}

void ManagerFirebase::uploadDatabase()
{
  timeClient.update();

  String path = "WSN1/data/";

  mData.Start();

  if (mData.errSensor(true))
  {
    setPath("WSN1/erorr_1");
    updateDataRealTime(1);
    return;
  }
  else if (mData.errSensor(false))
  {
    setPath("WSN1/erorr_2");
    updateDataRealTime(1);
    return;
  }

  /* set Database */

  setPath("WSN1/erorr/sensor_1");
  updateDataRealTime(0);
  setPath("WSN1/erorr/sensor_2");
  updateDataRealTime(0);

  setPath("WSN1/temperature/sensor_1");
  updateDataRealTime(mData.getTemp(true));
  setPath("WSN1/temperature/sensor_2");
  updateDataRealTime(mData.getTemp(false));

  setPath("WSN1/humidity/sensor_1");
  updateDataRealTime(mData.getHum(true));
  setPath("WSN1/humidity/sensor_2");
  updateDataRealTime(mData.getHum(false));

  setPath("WSN1/humiture/sensor_1");
  updateDataRealTime(mData.getHI(true));
  setPath("WSN1/humiture/sensor_2");
  updateDataRealTime(mData.getHI(false));

  /* set JSON */

  json.set("temperature/sensor_1", int(mData.getTemp(true)));
  json.set("temperature/sensor_2", int(mData.getTemp(false)));

  json.set("humidity/sensor_1", int(mData.getHum(true)));
  json.set("humidity/sensor_2", int(mData.getHum(false)));

  json.set("humiture/sensor_1", int(mData.getHI(true)));
  json.set("humiture/sensor_2", int(mData.getHI(false)));

  json.set("date", String(timeClient.getFormattedTime()));
  Firebase.pushJSON(fData, path, json);
}