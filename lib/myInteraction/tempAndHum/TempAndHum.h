#ifndef _TEMPANDHUM_H_
#define _TEMPANDHUM_H_

    #include <FBRtDatabase.h>
    #include <sensors/tempAndHumSensor/TempAndHumSensor.h>
    #include <digitalClock/DigitalClock.h>

    #define DHTPIN 22
    static String TEMPPATH = "/Temperature";
    static String HUMPATH = "/Humidity";
    static String TEMPKEY = "/temperatures";
    static String HUMKEY = "/humidities";

    static TempAndHumSensor dhtSensor = TempAndHumSensor(DHTPIN, DHTType::DHT11);
    static FBRtDatabase dhtDatabase = FBRtDatabase(HOST, AUTH, PATH, KEY);

    // return date: "dd-mm"
    String _today();

    void sendDhtData();

#endif