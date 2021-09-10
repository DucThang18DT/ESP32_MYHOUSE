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
    return true;
}

void disconnect(){
    WiFi.disconnect();
}

bool changeWifi(String ssid ="", String pass =""){
    if (connectWifi(ssid.c_str(), pass.c_str())){
        mySsid = ssid;
        myPass = pass;
        return true;
    }
    else connectWifi(mySsid.c_str(), myPass.c_str());
    return false;
}

String localIP(){
    return WiFi.localIP().toString();
}

void wifiStreamCallback(StreamData data){
    Serial.printf("\nstream path: %s\nevent path: %s\ndata type: %s\nevent type: %s\n\n",
        data.streamPath().c_str(),
        data.dataPath().c_str(),
        data.dataType().c_str(),
        data.eventType().c_str());
    Serial.println();   
    FBRtDatabase wifiData = FBRtDatabase(HOST, AUTH, "/", "");
    String _data = wifiData.getData("/Wifi");
    DynamicJsonDocument jsonData(200);
    deserializeJson(jsonData, _data);
    bool _connect = jsonData["Connect"].as<bool>();
    bool _change = jsonData["Change"].as<bool>();
    if (!_connect && _change){
        if (!changeWifi(jsonData["SSID"].as<String>(), jsonData["Pass"].as<String>())){
            jsonData["SSID"] = mySsid;
            jsonData["Pass"] = myPass;}
        jsonData["IP"] = localIP();
        jsonData["Connect"] = true;
        jsonData["Change"] = false;
        serializeJson(jsonData, _data);
        wifiData.sendData("Wifi", _data, Mode::update);
    }
    if (!_change && !_connect) disconnect();
}

void wifiStreamTimeOutCallback(bool timeOut){
    Serial.println("timeOut founction");
  if (timeOut)
    Serial.println("stream timeout, resuming...\n");
}