// #define ARDUINOJSON_ENABLE_COMMENTS 1
// #include <WiFiClient.h>

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

  referenceTime = referenceTime2 = referenceTime3 = millis();

  xTaskCreatePinnedToCore(
    alarm,
    "Check Alarm",
    5000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    0,           /* priority of the task */
    &Task2,      /* Task handle to keep track of created task */
    0);

  xTaskCreatePinnedToCore(
    dhtData,
    "DHT Data",
    5000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    0,           /* priority of the task */
    &Task3,      /* Task handle to keep track of created task */
    1);

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