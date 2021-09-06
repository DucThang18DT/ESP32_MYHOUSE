#include "FBRtDatabase.h"

FBRtDatabase::FBRtDatabase(String host ="", String auth="", String path ="/", String key = ""){
    _firebaseHost = host;
    _firebaseAuth = auth;
    _dataPath = path;
    _keyData = key;
}

void FBRtDatabase::setHost(String host = ""){
    _firebaseHost = host;
}

void FBRtDatabase::setAuth(String auth = ""){
    _firebaseAuth = auth;
}

void FBRtDatabase::setDataPath(String path = "/"){
    _dataPath = path;
}

void FBRtDatabase::setKeyData(String key = ""){
    _keyData = key;
}

void FBRtDatabase::setFirebaseInfor(String host ="", String auth=""){
    _firebaseHost = host;
    _firebaseAuth = auth;
}

void FBRtDatabase::connect(){
    Firebase.begin(_firebaseHost, _firebaseAuth);
    Firebase.reconnectWiFi(true);
}

String FBRtDatabase::getData(String path = "/"){
    Firebase.getJSON(_firebaseData, path);
    // Serial.println("\ngetData: " + _firebaseData.jsonString());
    return _firebaseData.jsonString();
}

int FBRtDatabase::getInt(String path = "/"){
    Firebase.getInt(_firebaseData, path);
    // Serial.println("\ngetInt: " + _firebaseData.intData());
    return _firebaseData.intData();
}

void FBRtDatabase::sendData(String path = "/", String jsonString = "", Mode mode = Mode::set){
    FirebaseJson _fbJson;
    _fbJson.setJsonData(jsonString);
    switch (mode)
    {
    case Mode::set:
        Firebase.setJSON(_firebaseData, path, _fbJson);
        Serial.println("\nset Data success!");
        break;
    case Mode::push:
        Firebase.push(_firebaseData, path, _fbJson);
        Serial.println("\npush Data success!");
    case Mode::update:
        Firebase.updateNode(_firebaseData, path, _fbJson);
        Serial.println("\nupdate Data success!");
        break;
    }
}

void FBRtDatabase::sendData(String path = "/", int num = 0, Mode mode = Mode::set){
    switch (mode)
    {
    case Mode::set:
        Firebase.setInt(_firebaseData, path, num);
        Serial.println("\nset Data success!");
        break;
    case Mode::push:
        Firebase.push(_firebaseData, path, num);
        Serial.println("\npush Data success!");
    case Mode::update:
        Firebase.updateNode(_firebaseData, path, num);
        Serial.println("\nupdate Data success!");
        break;
    }
}