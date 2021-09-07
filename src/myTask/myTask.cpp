#include "myTask.h"

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

void dhtData(void * parameters){
    Serial.print("\nTask_Alarm running on core: ");
    Serial.println(xPortGetCoreID());
    referenceTime3 = millis();

    for (;;){
        DigitalClock _clock = DigitalClock();
        if ((_clock.getMinutes() == 0) && (abs(millis() - referenceTime3) > 3e4)){
          referenceTime3 = millis(); 
          
          delay(50);
        }
        delay(100);
    }
    vTaskDelete(Task3);
}