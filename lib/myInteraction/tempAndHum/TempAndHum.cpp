#include "TempAndHum.h"

String _today(){
    String date ="", month = "";
    date += DigitalClock::getDate() <10 ? "0" + String(DigitalClock::getDate()): String(DigitalClock::getDate());
    month += DigitalClock::getMonth() <10 ? "0" + String(DigitalClock::getMonth()): String(DigitalClock::getMonth());
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