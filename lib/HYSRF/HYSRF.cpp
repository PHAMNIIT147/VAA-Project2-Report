#include "HYSRF.h"

HYSRF::HYSRF() : mDistance(0)
{
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);
}

void HYSRF::setDistance()
{

  u_long duration;

  digitalWrite(TRIG, 0);
  delayMicroseconds(2);

  digitalWrite(TRIG, 1);
  delayMicroseconds(10);
  digitalWrite(TRIG, 0);

  duration = pulseIn(ECHO, 1);

  this->mDistance = duration * 0.034 / 2;

  Serial.println("SRF05 Done!");
  delay(1000);
}

u_long HYSRF::getDistance()
{
  return this->mDistance;
}

bool HYSRF::isParking()
{
  setDistance();
  return (getDistance() > 5 && getDistance() < 20) ? true : false;
}

bool HYSRF::isError()
{
  digitalWrite(LED, 0);
  delay(100);
  Serial.print(mDistance);
  if (mDistance < 5 || mDistance == 0)
  {
    digitalWrite(LED, 1);
    delay(100);
    return true;
  }
  return false;
}
