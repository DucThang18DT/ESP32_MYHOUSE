#ifndef _FBRTINTERACTION_H_
#define _FBRTINTERACTION_H_

#include <Arduino.h>
#include <DeviceItem.h>
#include <FBRtDatabase.h>

static String HOST = "esp32firebase-1e567-default-rtdb.firebaseio.com";
static String AUTH = "eM8q1Ew73xkNkAmuy1DanDK0ND1FKMn7l4uAmmnu";
static String PATH = "/testUser1";
static String KEY = "users";
static FBRtDatabase fbDatatbase = FBRtDatabase(HOST, AUTH, PATH, KEY);
static FirebaseData(fbStreamData);
static std::vector<DeviceItem> listDevices = {};


void buildListDevices(std::vector<DeviceItem>*);
void splitString(std::vector<String>*, String, char);
// void streamCallback(StreamData);
void streamTimeOutCallback(bool);
void fbRtStream(FirebaseData*, String);

#endif