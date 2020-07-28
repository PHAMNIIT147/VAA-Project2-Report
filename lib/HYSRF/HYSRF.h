#ifndef HYSRF_H
#define HYSRF_H

#include <Arduino.h>

#define LED D2
#define TRIG D6
#define ECHO D7

class HYSRF
{
private:
  u_long mDistance;

  void setDistance();

public:
  HYSRF(/* args */);

  u_long getDistance();

  bool isError();
  bool isParking();
};

#endif //HYSRF_H