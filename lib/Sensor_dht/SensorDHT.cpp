#include "SensorDHT.h"

DHT dht_1(DHTPIN_1, DHTTYPE);
DHT dht_2(DHTPIN_2, DHTTYPE);

SensorDHT::SensorDHT(/* args */)
{
  pinMode(LED, OUTPUT);
  pinMode(FAN, OUTPUT);
}

void SensorDHT::init()
{
  dht_1.begin();
  dht_2.begin();
}

void SensorDHT::Start()
{
  uint8_t t_1 = dht_1.readTemperature();
  uint8_t h_1 = dht_1.readHumidity();
  uint8_t hi_1 = dht_1.computeHeatIndex(t_1, h_1, false);
  uint8_t t_2 = dht_2.readTemperature();
  uint8_t h_2 = dht_2.readHumidity();
  uint8_t hi_2 = dht_2.computeHeatIndex(t_2, h_2, false);

  if (((t_1 + t_2) / 2) > 38 && (t_1 < 254 || t_2 < 254))
  {
    startEmergency(1);
  }
  else
  {
    startEmergency(0);
  }

  this->dht1.mTemperature = t_1;
  this->dht1.mHumidity = h_1;
  this->dht1.mHumiture = hi_1;
  this->dht2.mTemperature = t_2;
  this->dht2.mHumidity = h_2;
  this->dht2.mHumiture = hi_2;
}

uint8_t SensorDHT::getTemp(bool select)
{

  return (select) ? this->dht1.mTemperature : this->dht2.mTemperature;
}

uint8_t SensorDHT::getHum(bool select)
{
  return (select) ? this->dht1.mHumidity : this->dht2.mHumidity;
}

uint8_t SensorDHT::getHI(bool select)
{
  return (select) ? this->dht1.mHumiture : this->dht2.mHumiture;
}

bool SensorDHT::errSensor(bool select)
{
  switch (select)
  {
  case true:
    return (getTemp(true) > 254 || getHum(true) > 254 || getHI(true) > 254) ? true : false;
    break;
  case false:
    return (getTemp(false) > 254 || getHum(false) > 254 || getHI(false) > 254) ? true : false;
    break;
  default:
    Serial.println("Not selected sensor");
    break;
  }
}

void startEmergency(int state)
{
  digitalWrite(LED, state);
  digitalWrite(FAN, !state);
}
