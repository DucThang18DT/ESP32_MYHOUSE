// #define ARDUINOJSON_ENABLE_COMMENTS 1
#include <WiFiClient.h>
#include <DeviceItem.h>
#include <FBRtDatabase.h>
#include <myWifi/myWifi.h>
#include <fbInter/FBRtInteraction.h>


// String HOST = "esp32firebase-1e567-default-rtdb.firebaseio.com";
// String AUTH = "eM8q1Ew73xkNkAmuy1DanDK0ND1FKMn7l4uAmmnu";
// String PATH = "/testUser1";
// String KEY = "users";

// #define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
// #define TIME_TO_SLEEP  7*60*60  /*second*/



void setup() {
  Serial.begin(115200);
  connectWifi(mySsid.c_str(), myPass.c_str());
  fbDatatbase.connect();
  
  buildListDevices();

  String jsonStr = DeviceItem::buildJson(&listDevices, KEY);
  fbDatatbase.sendData("/ESPTest/setTest1", jsonStr, Mode::set);

  fbRtStream(PATH);
  // stream(fbDatatbase.dataPath());

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
