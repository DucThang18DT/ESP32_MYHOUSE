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
    Serial.println("\ngetData: " + _firebaseData.jsonString());
    return _firebaseData.jsonString();
}