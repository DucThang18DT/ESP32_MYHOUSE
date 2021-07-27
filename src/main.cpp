// #define ARDUINOJSON_ENABLE_COMMENTS 1
#include <ArduinoJson.h>
// #include <WiFi.h>
#include <WiFiClient.h>
#include "myWifi/myWifiConnect.cpp"
#include <DeviceItem.h>
#include <FBRtDatabase.h>
#include <vector>

String HOST = "esp32firebase-1e567-default-rtdb.firebaseio.com";
String AUTH = "eM8q1Ew73xkNkAmuy1DanDK0ND1FKMn7l4uAmmnu";
String PATH = "/testUser1";
String key = "users";

static std::vector<DeviceItem> listDevices;
FBRtDatabase fbDatatbase = FBRtDatabase(HOST, AUTH, PATH, key);
// #define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
// #define TIME_TO_SLEEP  7*60*60  /*second*/

void setup() {
  Serial.begin(115200);
  connectWifi(mySsid.c_str(), myPass.c_str());
  fbDatatbase.connect();
  String dataRcv = fbDatatbase.getData(PATH);
  Serial.printf("\nData Received: \n");
  Serial.println(dataRcv);
  DeviceItem::buildListObjects(&listDevices, dataRcv, key);

//   WiFi.disconnect();
//   WiFi.mode(WIFI_AP);
//   WiFi.softAPConfig(ip, gateway, subnet);
//   WiFi.softAP(ssid, pass);
//   WiFi.begin(ssid,pass);
//   while (WiFi.status() != WL_CONNECTED){
//       Serial.printf(".");
//       delay(500);}
//   Serial.printf("\nConnected!\nIP address: ");
//   Serial.println(WiFi.localIP());
}

void loop() {
  
}

// void mainpage(){
//   String s = FPSTR(MainPage);
//   webServer.send(200, "text/html",s);
//   Serial.printf("\nMainPage\n");  
// }
// void logIn(){
//   String s = FPSTR(LogIn);
//   webServer.send(200, "text/html",s);
//   Serial.printf("\nlogIn\n");  
// }

// void Valid(){
//   String str_user = webServer.arg("User");
//   String str_pass = webServer.arg("Pass");
//   if ((str_user == username) && (str_pass == password))
//     mainpage();
// }

// void logOut(){
//   logIn();
// }

// void butState(){
//   String str_dv = webServer.arg("Button");
//   int dv = (int)str_dv[0] - 48;
//   if (!dv && DV[0].deviceStt()){
//     DV[dv].inverse();
//     if (!dv && !DV[dv].deviceStt())
//       for (int i = 1; i < tDevice; i++) DV[i].turnOff();
//   }
// }

// void upButtonStt(){
//   DynamicJsonDocument  doc(200);
//   JsonArray data = doc.createNestedArray("Stt");
//   for (int i = 0; i < tDevice; i++)
//     if (DV[i].deviceStt()) data.add("ON");
//     else data.add("OFF");
//   String json;
//   serializeJson(doc, json);
//   webServer.send(200,"application/json",json);
// }

// void editDVName(){
//   String str_dv = webServer.arg("device");
//   String str_name = webServer.arg("name");
//   DV[str_dv[0]-48].changeName(str_name);
// }

// void updateTimer(){
//   String str_dv = webServer.arg("device");
//   int _alarm[4] = {0,0,0,0};
//   _alarm[0] = DV[str_dv[0] - 48].Alarm/3600;
//   _alarm[1] = (DV[str_dv[0] - 48].Alarm - _alarm[0]*60)/60;
//   _alarm[2] = DV[str_dv[0] - 48].turnOffTimer/3600;
//   _alarm[3] = (DV[str_dv[0] - 48].turnOffTimer - _alarm[2]*60)/60;
//   DynamicJsonDocument  doc(200);
  
//   JsonArray alarm = doc.createNestedArray("alrms");
//   for (int i = 0; i < 4; i++)
//     alarm.add(_alarm[i]);
//   JsonArray option = doc.createNestedArray("options");
//   for (int i = 0; i < 3; i++)
//     option.add(DV[str_dv[0] - 48].repeat(i));
//   JsonArray day = doc.createNestedArray("days");
//   for (int i = 0; i < 7; i++)
//     day.add(DV[str_dv[0] - 48].day(i));

//   String json;
//   serializeJson(doc, json);
//   webServer.send(200,"application/json",json);
// }

// void Alarm(){
//   String str_Timer = webServer.arg("Timer");
//   DynamicJsonDocument doc(2048);
//   deserializeJson(doc, str_Timer);
  
//   //doc["time"].as<long>()
//   int dv = doc["device"].as<int>();
//   int _alarm[4] = {0,0,0,0};
//   for (int i = 0; i < 4; i++)
//     _alarm[i] = doc["alarms"][i];
//   DV[dv].Alarm = _alarm[0]*3600 + _alarm[1]*60;
//   DV[dv].turnOffTimer = _alarm[2]*3600 + _alarm[3]*60;
//   DV[dv].updateAlarm();
//   for (int i = 0; i < 3; i++)
//     DV[dv].changeRepeat(i, doc["options"][i]);
//   for (int i = 0; i < 7; i++)
//     DV[dv].changeDay(i, doc["days"][i]);
// }

// void disconnectWifi(){
//   WiFi.disconnect();
// }

// bool wifiConnect(char *ssid, char *pass){
//   disconnectWifi();
//   WiFi.begin(ssid,pass);
//   while (WiFi.status() != WL_CONNECTED){
//       Serial.printf(".");
//       delay(500);
//       if ((WiFi.status() == WL_NO_SSID_AVAIL ) || (WiFi.status() == WL_CONNECT_FAILED))
//         return false;
//       }
//   Serial.printf("\nConnected!\nIP address: ");
//   Serial.println(WiFi.localIP());
//   return true;
// }

// void updateWifi(){
//   String _ssid = webServer.arg("ssid");
//   String _pass = webServer.arg("pass");
//   char _SSID[50]; _ssid.toCharArray(_SSID, _ssid.length());
//   char _PASS[50]; _pass.toCharArray(_PASS, _pass.length());
//   DynamicJsonDocument  doc(200);
//   if (wifiConnect(_SSID, _PASS)){
//     strcpy(_SSID, ssid);
//     strcpy(_PASS, pass);
//     doc["state"] = true;
//   }
//   else {
//     wifiConnect(ssid, pass);
//     doc["state"] = false;
//   }
//   doc["ssid"] = ssid;
//   doc["ip"] = WiFi.localIP();
//   String json;
//   serializeJson(doc, json);
//   webServer.send(200,"application/json",json);
// }
// void updateDisplay(){
//   DynamicJsonDocument  doc(200);
//   doc["temp"] = 25;
//   doc["hum"] = 60;
//   String json;
//   serializeJson(doc, json);
//   webServer.send(200,"application/json",json);
// }