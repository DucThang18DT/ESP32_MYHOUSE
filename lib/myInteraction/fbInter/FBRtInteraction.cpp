#include "FBRtInteraction.h"

void buildListDevices(std::vector<DeviceItem>* list){
  // Serial.printf("\n(Build list devices) size of listDevice = %d\n", list->size());
  while (list->size() > 0) list->pop_back();
  list->resize(0);

  // Serial.printf("\n(Build list devices) size of listDevice after = %d\n", list->size());
  // Serial.printf("\n(Build list devices) capacity of listDevice after = %d\n", list->capacity());

  int length = fbDatatbase.getInt(PATH + "/length");
  // Serial.printf("\n(build list devices) length of list: \n");
  // Serial.println(length);
  for (int i = 0; i < length; i++){
    String dataRcv = fbDatatbase.getData(PATH + "/" + KEY + "/" + String(i));
    // Serial.printf("\n(build list devices) data of device %d: \n", i);
    // Serial.println(dataRcv);
    if ((dataRcv != NULL) || (dataRcv != ""))
      DeviceItem::addObject(&(*list), dataRcv);
  }
  // Serial.printf("\n(build list devices) size of listDevice = %d\n", list->size());
}

void splitString(std::vector<String> *listKeys,String str = "", char symbol = '/'){
  // Serial.println("\n(split String) List key:");
  while (str.length() > 0){
    if (str.charAt(0) == '/') str = str.substring(1);
    listKeys->push_back(str.substring(0, str.indexOf('/')));
    // Serial.println(listKeys->at(listKeys->size()-1));
    str = str.substring(str.indexOf('/'));
  }
}

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

      String dataRcv = fbDatatbase.getData(PATH + "/" + listKeys.at(0) + "/" + listKeys.at(1));
      
      DeviceItem::updateObject(&listDevices, positionOfDevice, dataRcv);
    }
}

void streamTimeOutCallback(bool timeOut){
  Serial.println("timeOut founction");
  if (timeOut)
    Serial.println("stream timeout, resuming...\n");
}

// void fbRtStream(FirebaseData *_fbStreamData, String path = "/"){
//     Firebase.beginStream(*_fbStreamData, path);
//     Firebase.setStreamCallback(*_fbStreamData, streamCallback, streamTimeOutCallback);
// }

