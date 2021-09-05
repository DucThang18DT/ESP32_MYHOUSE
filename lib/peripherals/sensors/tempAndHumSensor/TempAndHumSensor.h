#ifndef _TEMPANDHUMSENSOR_H_
#define _TEMPANDHUMSENSOR_H_

#include <DHTesp.h>

enum DHTType{DHT11, DHT22};


class TempAndHumSensor
{
private:
    int _pin;
    DHTType _type;
    DHTesp dht;
public:
    TempAndHumSensor(int, DHTType);
    ~TempAndHumSensor(){}

    int tempNow();
    int humNow();
};

#endif