#ifndef _FBRTINTERACTION_H_
#define _FBRTINTERACTION_H_

#include <Arduino.h>
#include <DeviceItem.h>
#include <FBRtDatabase.h>

static String PATH = "/testUser1";
static String KEY = "users";
static FBRtDatabase fbDatatbase = FBRtDatabase(HOST, AUTH, PATH, KEY);
static FirebaseData(fbStreamData);
static std::vector<DeviceItem> listDevices = {};


// void buildListObjects(std::vector<DeviceItem>* , String, String);
void buildListDevices(std::vector<DeviceItem>*);
void splitString(std::vector<String>*, String, char);
void streamCallback(StreamData);
void streamTimeOutCallback(bool);
void fbRtStream(FirebaseData*, String);

#endif