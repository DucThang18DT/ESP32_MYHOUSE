// #define ARDUINOJSON_ENABLE_COMMENTS 1
// #include <WiFiClient.h>
#include <DeviceItem.h>
#include <FBRtDatabase.h>
#include <fbInter/FBRtInteraction.h>
#include <myWifi/myWifi.h>
#include <digitalClock/DigitalClock.h>
#include <sensors/tempAndHumSensor/TempAndHumSensor.h>
#include <myTask/myTask.h>

unsigned long referenceTime;

void setup() {
  Serial.begin(115200);
  connectWifi(mySsid.c_str(), myPass.c_str());
  fbDatatbase.connect();
  
  buildListDevices(&listDevices);
  delay(1000);
  String jsonStr = DeviceItem::buildJson(&listDevices, KEY);
  fbDatatbase.sendData("/ESPTest/setTest1", jsonStr, Mode::set);
  

  Firebase.beginStream(fbStreamData, "/testUser1");
  Serial.println("(main) begin Stream");
  Firebase.setStreamCallback(fbStreamData, streamCallback, streamTimeOutCallback);
  Serial.println("(main) set Stream callback: OK");

  referenceTime = millis();

  xTaskCreatePinnedToCore(
    alarm,
    "Check Alarm",
    5000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    0,           /* priority of the task */
    &Task2,      /* Task handle to keep track of created task */
    0);

  Serial.printf("\nRunning on core: ");
  Serial.println(xPortGetCoreID());
}

void loop() {
  if (abs(millis() - referenceTime >= 10000)){
    referenceTime = millis();
    Serial.println("\n-------List Devices-------");
    for (int i = 0; i< listDevices.size(); i++){
      Serial.println(listDevices.at(i).name());
    }
    DigitalClock myDClock;
    myDClock.showDate();
    delay(80);
  }
}