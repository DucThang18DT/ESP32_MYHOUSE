#ifndef _MYWIFI_H_
#define _MYWIFI_H_

#include <Arduino.h>
#include <WiFi.h>

static String mySsid = "HT709";
static String myPass = "hienthuong";
bool connectWifi(const char*, const char*);

#endif