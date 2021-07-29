#include "DeviceItem.h"

DeviceItem::DeviceItem(String name, int id, int pinName, Status status, bool timer, bool timerOnState, bool timerOffState, TypeStatus typeState,
                       int timerOn, int timerOff, Repeat repeat, bool *days)
{
  newName(name);
  newId(id);
  newPinName(pinName);
  newTypeState(typeState);
  newState(status);
  newTimer(timer);
  newTimerOnState(timerOnState);
  newTImerOffState(timerOffState);
  newTimerOn(timerOn);
  newTimerOff(timerOff);
  newRepeat(repeat);
  newDays(days);
}

DeviceItem::DeviceItem(String name, int id, int pinName)
{
  newName(name);
  newId(id);
  newPinName(pinName);

  newTypeState(TypeStatus::OnOff);
  newState(Status::OFF);
  newTimer(false);
  newTimerOnState(false);
  newTImerOffState(false);
  newTimerOn(-1);
  newTimerOff(-1);
  newRepeat(Repeat::Once);
  bool days[] = {false, false, false, false, false, false, false};
  newDays(days);
}

void DeviceItem::newDays(bool *day)
{
  for (int i = 0; i < (sizeof(_days) / sizeof(bool)); i++)
  {
    _days[i] = day[i];
  }
}

void DeviceItem::newTypeState(TypeStatus type = TypeStatus::OnOff)
{
  _typeState = type;
  switch (_typeState)
  {
  case TypeStatus::OnOff:
    if (_state == Status::OPEN || _state == Status::ON)
      _state = Status::ON;
    else
      _state = Status::OFF;
    break;
  case TypeStatus::OpenClose:
    if (_state == Status::OPEN || _state == Status::ON)
      _state = Status::OPEN;
    else
      _state = Status::CLOSE;
    break;
  }
}

void DeviceItem::newState(Status state = Status::OFF)
{
  switch (_typeState)
  {
  case TypeStatus::OnOff:
    if ((state == Status::CLOSE) || (state == Status::OFF))
      _state = Status::OFF;
    else
      _state = Status::ON;
    break;
  case TypeStatus::OpenClose:
    if ((state == Status::CLOSE) || (state == Status::OFF))
      _state = Status::CLOSE;
    else
      _state = Status::OPEN;
    break;
  }
}

void DeviceItem::changeState()
{
  switch (_typeState)
  {
  case TypeStatus::OnOff:
    if (_state == Status::ON)
      _state = Status::OFF;
    else
      _state = Status::ON;
    break;
  case TypeStatus::OpenClose:
    if (_state == Status::OPEN)
      _state = Status::CLOSE;
    else
      _state = Status::OPEN;
    break;
  }
}

void DeviceItem::newDay(int index = 0, bool value = false){
  _days[index] = value;
  bool isEveryday = true;
    for (int i = 0; i < (sizeof(_days)/sizeof(bool)); i++)
      if (_days[i] == false) {
        isEveryday = false;
        break;
      }
    if (isEveryday) {
      newRepeat(Repeat::Everyday);
      bool days[] = {false, false, false, false, false, false, false};
      newDays(days);
    }  
}

void DeviceItem::turnOff(){
  newState(Status::OFF);
}

void DeviceItem::setTimerOn(int hour = 0, int minute = -1){
  if (minute < 0)
      _timerOn = -1;
    else if (hour >= 0 && minute >= 0) _timerOn = hour * 3600 + minute * 60;
}

void DeviceItem::setTimerOff(int hour = 0, int minute = -1){
  if (minute < 0)
      _timerOn = -1;
    else if (hour >= 0 && minute >= 0) _timerOff = hour * 3600 + minute * 60;
}

int DeviceItem::getHourOn(){
  if (_timerOn > -1)
      return _timerOn / 3600;
  else
    return 0;
}

int DeviceItem::getMinuteOn(){
  if (_timerOn > -1)
      return _timerOn / 60 - (_timerOn / 3600) * 60;
    else
      return -1;
}

int DeviceItem::getHourOff(){
  if (_timerOff > -1)
      return _timerOff / 3600;
  else
    return 0;
}

int DeviceItem::getMinuteOff(){
  if (_timerOff > -1)
      return _timerOff / 60 - (_timerOff / 3600) * 60;
    else
      return -1;
}

void DeviceItem::buildListObjects(std::vector<DeviceItem> listItems[], String jsonString, String key =""){
  while (listItems->size() > 0) listItems->pop_back();
  DynamicJsonDocument json(1024*100);
  deserializeJson(json, jsonString);
  Serial.printf("\nJson: ");
  Serial.printf(json[key][0]["name"]);
  Serial.println("\nlistDevices: ");
  for (int i = 0; i < json["length"].as<int>(); i++){
    bool _days[7];
    for (int j = 0; j<7; j++)
    _days[j] = json[key][i]["days"][j].as<bool>();
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
  Serial.println("\nComplete build list devices");
}

void DeviceItem::updateObject(std::vector<DeviceItem> listItems[],int index, String jsonString){
  DynamicJsonDocument json(1024);
  deserializeJson(json, jsonString);
  Serial.printf("\nJson: ");
  Serial.printf(json["name"]);
  Serial.println("\nlistDevices: ");

  bool _days[7];
  for (int j = 0; j<7; j++)
  _days[j] = json["days"][j].as<bool>();
  listItems->at(index) = DeviceItem(
    json["name"].as<String>(),
    json["id"].as<int>(),
    json["pinName"].as<int>(),
    (json["status"].as<int>() == 1)? Status::ON:Status::OFF,
    json["timer"].as<bool>(),
    json["timerOnState"].as<bool>(),
    json["timerOffState"].as<bool>(),
    (json["typeState"].as<int>() == 1)? TypeStatus::OnOff:TypeStatus::OpenClose,
    json["timerOn"].as<int>(),
    json["timerOff"].as<int>(),
    (json["repeat"].as<int>() == 0) ? Repeat::Once :(json["repeat"].as<int>() == 1 ? Repeat::Everyday:Repeat::Option),
    _days
  );
  Serial.println(listItems->at(index).name());
  Serial.println("\nComplete update object");
}

String DeviceItem::buildJson(std::vector<DeviceItem> listItems[], String key = ""){
  Serial.printf("\nlist Size: ");
  Serial.println(listItems->size());
  DynamicJsonDocument doc(1024*listItems->size()); // size of doc equal size of listItems * 1 Mb.
  for (int i = 0; i < listItems->size(); i++){
    doc[key][i]["name"] = listItems->at(i).name();
    doc[key][i]["id"] = listItems->at(i).id();
    doc[key][i]["pinName"] = listItems->at(i).pinName();
    doc[key][i]["status"] = ((listItems->at(i).status() == Status::ON) || (listItems->at(i).status() == Status::OPEN))? 1 : 0;
    doc[key][i]["timer"] = listItems->at(i).timer();
    doc[key][i]["timerOnState"] = listItems->at(i).timerOnState();
    doc[key][i]["timerOffState"] = listItems->at(i).timerOffState();
    doc[key][i]["typeState"] = (listItems->at(i).typeState() == TypeStatus::OnOff)?0:1;
    doc[key][i]["timerOn"] = listItems->at(i).timerOn();
    doc[key][i]["timerOff"] = listItems->at(i).timerOff();
    doc[key][i]["repeat"] = (listItems->at(i).repeat() == Repeat::Everyday) ? 0 : (listItems->at(i).repeat() == Repeat::Once ? 1 :2);
    for (int j = 0; j <7; j++)
      doc[key][i]["days"][j] = listItems->at(i).day(j);
  }
  String jsonString;
  serializeJson(doc, jsonString);
  Serial.println("\nJson String: \n" + jsonString);
  return jsonString;
}

String DeviceItem::toJson(){
  DynamicJsonDocument doc(1024); // size of doc is * 1 Mb.
    doc["name"] = name();
    doc["id"] = id();
    doc["pinName"] = pinName();
    doc["status"] = ((status() == Status::ON) || (status() == Status::OPEN))? 1 : 0;
    doc["timer"] = timer();
    doc["timerOnState"] = timerOnState();
    doc["timerOffState"] = timerOffState();
    doc["typeState"] = (typeState() == TypeStatus::OnOff)?0:1;
    doc["timerOn"] = timerOn();
    doc["timerOff"] = timerOff();
    doc["repeat"] = (repeat() == Repeat::Everyday) ? 0 : (repeat() == Repeat::Once ? 1 :2);
    for (int j = 0; j <7; j++)
      doc["days"][j] = day(j);
  
  String jsonString;
  serializeJson(doc, jsonString);
  Serial.println("\nJson String: \n" + jsonString);
  return jsonString;
}

// String name, int id, int pinName, Status status, bool timer, bool timerOnState, bool timerOffState, TypeStatus typeState,
//                        int timerOn, int timerOff, Repeat repeat, bool *days