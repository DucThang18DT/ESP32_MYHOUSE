#include "myWifi.h"

bool connectWifi(const char* ssid ="", const char* pass =""){
    WiFi.disconnect();
    WiFi.begin(ssid, pass);
    unsigned long referenceTime = millis();
    Serial.printf("Connecting to %s", ssid);
    while (WiFi.status() != WL_CONNECTED)
    {  
        delay(500);
        Serial.print(".");
        if (abs(millis() - referenceTime) >= 10000) {
            Serial.println("Cannot connect to this Wifi network!");
            return false;}
    }
    Serial.printf("\nConnected\nIP address: ");
    Serial.println(WiFi.localIP());
    mySsid = String(ssid);
    myPass = String(pass);
    return true;
}