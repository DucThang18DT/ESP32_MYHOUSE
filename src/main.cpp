// #define ARDUINOJSON_ENABLE_COMMENTS 1
// #include <WiFiClient.h>
#include <DeviceItem.h>
#include <FBRtDatabase.h>
#include <fbInter/FBRtInteraction.h>
#include <myWifi/myWifi.h>

unsigned long referenceTime;
unsigned long referenceTime2;
TaskHandle_t Task2;
void alarm(void *);

void streamCallback(StreamData data){
  Serial.printf("\nstream path: %s\nevent path: %s\ndata type: %s\nevent type: %s\n\n",
                data.streamPath().c_str(),
                data.dataPath().c_str(),
                data.dataType().c_str(),
                data.eventType().c_str());
    Serial.println();
    String path = data.dataPath();
    if (path == "/length") buildListDevices(&listDevices);
    else if (path.length()>1){
      std::vector<String> listKeys;
      splitString(&listKeys, path, '/');
      int positionOfDevice = listKeys.at(1).toInt();
      // Serial.printf("\n(streamCallback) position: %d", positionOfDevice);

      String dataRcv = fbDatatbase.getData(PATH + "/" + listKeys.at(0) + "/" + listKeys.at(1));
      
      // Serial.printf("\n(streamcallback) Data Received: \n");
      // Serial.println(dataRcv);
      // Serial.printf("(streamcallback) list size: %d", listDevices.size());
      DeviceItem::updateObject(&listDevices, positionOfDevice, dataRcv);
      // TODO
    }
}

void setup() {
  Serial.begin(115200);
  connectWifi(mySsid.c_str(), myPass.c_str());
  fbDatatbase.connect();
  
  buildListDevices(&listDevices);
  delay(1000);
  // Serial.printf("\n(main) size of listDevices: %d\n", listDevices.size());
  String jsonStr = DeviceItem::buildJson(&listDevices, KEY);
  fbDatatbase.sendData("/ESPTest/setTest1", jsonStr, Mode::set);
  
  // fbRtStream(&fbStreamData, PATH);

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
  }
}

void alarm(void * parameters){
  Serial.print("\nTask_Alarm running on core: ");
  Serial.println(xPortGetCoreID());

  for (;;){
    if (abs(millis() - referenceTime2) >= 5000){
      Serial.println("(Core 0) check alarm");
      referenceTime2 = millis();
      delay(100);

      for (int i = 0; i < listDevices.size(); i++){
        if (listDevices.at(i).isTimeToOn() || listDevices.at(i).isTimeToOff()) {
          String json = listDevices.at(i).toJson();
          fbDatatbase.sendData(PATH + "/" + KEY + "/" + String(i), json, Mode::update);
          Serial.printf("\n(alarm) sendData success!");
          delay(50);
        }
      }
      delay(100);
    }
  }
  vTaskDelete(Task2);
}