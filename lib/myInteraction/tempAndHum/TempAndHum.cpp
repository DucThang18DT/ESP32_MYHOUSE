#include "TempAndHum.h"

String _today(){
    DigitalClock clock = DigitalClock();
    String date ="", month = "";
    date += clock.getDate() <10 ? "0" + String(clock.getDate()): String(clock.getDate());
    month += clock.getMonth() <10 ? "0" + String(clock.getMonth()): String(clock.getMonth());
    return date + "-" + month;
}

void sendDhtData(){
    int tempLength = dhtDatabase.getInt(TEMPPATH + "/length");
    dhtDatabase.sendData(TEMPPATH + "/Dates/" + _today() + "/" + String(tempLength), String(dhtSensor.tempNow()), Mode::set);
    dhtDatabase.sendData(TEMPPATH + "/length", tempLength + 1, Mode::update);
    int humLength = dhtDatabase.getInt(HUMPATH + "/length");
    dhtDatabase.sendData(HUMPATH + "/Dates/" + _today() + "/" + String(humLength), String(dhtSensor.humNow()), Mode::set);
    dhtDatabase.sendData(HUMPATH + "/length", humLength + 1, Mode::update);
}