#include "myTask.h"

void alarm(void * parameters){
  Serial.print("\nTask_Alarm running on core: ");
  Serial.println(xPortGetCoreID());
  unsigned long referenceTime = millis();

  for (;;){
    if (abs(millis() - referenceTime) >= 5000){
      Serial.println("(Core 0) check alarm");
      referenceTime = millis();
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

void dhtData(void * parameters){
    Serial.print("\nTask_Alarm running on core: ");
    Serial.println(xPortGetCoreID());
    unsigned long referenceTime = millis();

    for (;;){
        DigitalClock _clock = DigitalClock();
        if ((_clock.getMinutes() == 0) && (abs(millis() - referenceTime) > 3e4)){
          referenceTime = millis(); 
          sendDhtData();
          delay(50);
        }
        delay(100);
    }
    vTaskDelete(Task3);
}

void wifiData(void * parameters){
  Serial.print("\nwifiData running on core: ");
  Serial.println(xPortGetCoreID());
  FirebaseData(wifiData);
  Firebase.beginStream(wifiData, "/Wifi");
  Serial.println("(main) begin Stream");
  Firebase.setStreamCallback(wifiData, wifiStreamCallback, wifiStreamTimeOutCallback);
  Serial.println("(main) set Stream callback: OK");

  delay(200);
  vTaskDelete(Task4);
}