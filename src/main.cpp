// #define ARDUINOJSON_ENABLE_COMMENTS 1
#include <WiFiClient.h>
#include <DeviceItem.h>
#include <FBRtDatabase.h>
#include <myInteraction/myWifi/myWifi.h>
#include <myInteraction/fbInter/FBRtInteraction.h>

void setup() {
  Serial.begin(115200);
  connectWifi(mySsid.c_str(), myPass.c_str());
  fbDatatbase.connect();
  
  buildListDevices();

  String jsonStr = DeviceItem::buildJson(&listDevices, KEY);
  fbDatatbase.sendData("/ESPTest/setTest1", jsonStr, Mode::set);

  fbRtStream(PATH);
}

void loop() {
  
}
