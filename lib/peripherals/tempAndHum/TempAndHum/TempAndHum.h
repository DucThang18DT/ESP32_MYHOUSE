#ifndef _TEMPANDHUM_H_
#define _TEMPANDHUM_H_

    #include <sensors/tempAndHumSensor/TempAndHumSensor.h>
    #define DHTPIN 22

    TempAndHumSensor tAHSensor = TempAndHumSensor(DHTPIN, DHTType::DHT11);

    void dhtStreamCallback(StreamData);

#endif