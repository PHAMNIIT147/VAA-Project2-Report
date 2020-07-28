#ifndef SENSOR_DHT_H
#define SENSOR_DHT_H

#include <DHT.h>
#include <Wire.h>

#define DHTPIN_1 D5
#define DHTPIN_2 D6
#define DHTTYPE DHT11
#define LED D7
#define FAN D2

typedef struct
{
  uint8_t mTemperature;
  uint8_t mHumidity;
  uint8_t mHumiture;
} Sensor;

class SensorDHT
{
private:
  Sensor dht1;
  Sensor dht2;

public:
  SensorDHT();

  void init();

  void Start();

  uint8_t getTemp(bool select);
  uint8_t getHum(bool select);
  uint8_t getHI(bool select);

  bool errSensor(bool select);
};

void startEmergency(int state);

#endif //SENSOR_DHT_H