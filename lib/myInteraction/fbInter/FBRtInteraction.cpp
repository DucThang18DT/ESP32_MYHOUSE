#include "FBRtInteraction.h"

void buildListObjects(std::vector<DeviceItem> listItems[], String jsonString, String key =""){
  Serial.printf("\n(DeviceItem::Build list object) size of listDevice = %d\n", listItems->size());
  while (listItems->size() > 0) listItems->pop_back();
  listItems->resize(0);
  Serial.printf("\n(DeviceItem::Build list object) size of listDevice after = %d\n", listItems->size());
  Serial.printf("\n(DeviceItem::Build list object) capacity of listDevice after = %d\n", listItems->capacity());
  Serial.printf("\n(DeviceItem::Build list object) key = %s\n", key.c_str());
  DynamicJsonDocument json(1024*100);
  // json->clear();
  deserializeJson(json, jsonString);
  json.shrinkToFit();
  Serial.printf("\n(DeviceItem::build list object) json size: %d", json.size());
  Serial.printf("\nJson: ");
  Serial.printf(json[key][0]["name"]);
  Serial.println("\nlistDevices: ");
  for (int i = 0; i < json["length"].as<int>(); i++){
    bool _days[7];
    for (int j = 0; j<7; j++)
    {_days[j] = json[key][i]["days"][j].as<bool>();
    Serial.printf("\n(DeviceItem::buildlistObject) _days[%d] : ",j);
    Serial.println(_days[j]);}
    listItems->push_back(DeviceItem(
      json[key][i]["name"].as<String>(),
      json[key][i]["id"].as<int>(),
      json[key][i]["pinName"].as<int>(),
      (json[key][i]["status"].as<int>() == 1)? Status::ON:Status::OFF,
      json[key][i]["timer"].as<bool>(),
      json[key][i]["timerOnState"].as<bool>(),
      json[key][i]["timerOffState"].as<bool>(),
      (json[key][i]["typeState"].as<int>() == 1)? TypeStatus::OnOff:TypeStatus::OpenClose,
      json[key][i]["timerOn"].as<int>(),
      json[key][i]["timerOff"].as<int>(),
      (json[key][i]["repeat"].as<int>() == 0) ? Repeat::Once :(json[key][i]["repeat"].as<int>() == 1 ? Repeat::Everyday:Repeat::Option),
      _days
    ));
    Serial.println(listItems->at(i).name());
  }
  Serial.printf("\n(DeviceItem::build list object) json size: %d", json.size());
  Serial.printf("\n(DeviceItem::build list object) list size: %d", listItems->size());
  json.remove(key);
  json.remove("users");
  json.remove("length");
  json.clear();
  Serial.printf("\n(DeviceItem::build list object) json size affter: %d", json.size());
  Serial.println("\n(DeviceItem::Build list object) Complete build list devices");
}

void buildListDevices(std::vector<DeviceItem>* list){
  String dataRcv = fbDatatbase.getData(PATH);
  Serial.printf("\n(build list devices) Data Received: \n");
  Serial.println(dataRcv);
  buildListObjects(&(*list), dataRcv, KEY);
  // Serial.printf("\nName [0]: %s", listDevices.at(0).name());
  Serial.printf("\n(build list devices) size of listDevice = %d\n", list->size());
}

void splitString(std::vector<String> *listKeys,String str = "", char symbol = '/'){
  Serial.println("\n(split String) List key:");
  while (str.length() > 0){
    if (str.charAt(0) == '/') str = str.substring(1);
    listKeys->push_back(str.substring(0, str.indexOf('/')));
    Serial.println(listKeys->at(listKeys->size()-1));
    str = str.substring(str.indexOf('/'));
  }
}

// void streamCallback(StreamData data){
//   Serial.printf("\nstream path: %s\nevent path: %s\ndata type: %s\nevent type: %s\n\n",
//                 data.streamPath().c_str(),
//                 data.dataPath().c_str(),
//                 data.dataType().c_str(),
//                 data.eventType().c_str());
//     Serial.println();
//     String path = data.dataPath();
//     if (path == "/length") buildListDevices(&listDevices);
//     else if (path.length()>1){
//       std::vector<String> listKeys;
//       splitString(&listKeys, path, '/');
//       int positionOfDevice = listKeys.at(1).toInt();

//       String dataRcv = fbDatatbase.getData(PATH + "/" + listKeys.at(0) + "/" + listKeys.at(1));
      
//       Serial.printf("\n(streamcallback) Data Received: \n");
//       Serial.println(dataRcv);
//       Serial.printf("(streamcallback) list size: %d", listDevices.size());
//       DeviceItem::updateObject(listDevices, positionOfDevice, dataRcv);
//       // TODO
//     }
// }

void streamTimeOutCallback(bool timeOut){
  Serial.println("timeOut founction");
  if (timeOut)
    Serial.println("stream timeout, resuming...\n");
}

// void fbRtStream(FirebaseData *_fbStreamData, String path = "/"){
//     Firebase.beginStream(*_fbStreamData, path);
//     Firebase.setStreamCallback(*_fbStreamData, streamCallback, streamTimeOutCallback);
// }