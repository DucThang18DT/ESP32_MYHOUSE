#include "TempAndHumSensor.h"

TempAndHumSensor::TempAndHumSensor(int pin, DHTType type){
    _pin = pin;
    _type = type;
    if( _type == DHTType::DHT11)
        dht.setup(_pin, DHTesp::DHT11);
    else dht.setup(_pin, DHTesp::DHT22);
}

int TempAndHumSensor::tempNow(){
    return round(dht.getNumberOfDecimalsTemperature());
}

int TempAndHumSensor::humNow(){
    return round(dht.getNumberOfDecimalsHumidity());
}