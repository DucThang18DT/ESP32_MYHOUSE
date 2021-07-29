// #define ARDUINOJSON_ENABLE_COMMENTS 1
#include <WiFiClient.h>
#include <DeviceItem.h>
#include <FBRtDatabase.h>
#include <myInteraction/myWifi/myWifi.h>
#include <myInteraction/fbInter/FBRtInteraction.h>

unsigned long referenceTime;
void setup() {
  Serial.begin(115200);
  connectWifi(mySsid.c_str(), myPass.c_str());
  fbDatatbase.connect();
  
  buildListDevices(&listDevices);
  delay(1000);
  Serial.printf("\nsize of listDevice: %d\n", listDevices.size());
  String jsonStr = DeviceItem::buildJson(&listDevices, KEY);
  fbDatatbase.sendData("/ESPTest/setTest1", jsonStr, Mode::set);

  // fbRtStream(PATH);
  referenceTime = millis();
}

void loop() {
  // if (abs(millis() - referenceTime >= 3000)){
  //   Serial.println("\nList Devices: ");
  //   for (int i = 0; i< listDevices.size(); i++){
  //     Serial.println(listDevices.at(i).name());
  //   }
  // }
}
