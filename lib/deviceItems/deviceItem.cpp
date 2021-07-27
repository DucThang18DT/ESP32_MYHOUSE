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
  DynamicJsonDocument json(2048);
  deserializeJson(json, jsonString);
  Serial.printf("\nJson: ");
  Serial.printf(json[key][0]["name"]);
  Serial.println("\nlistDevices: ");
  // becareful: the condition of for loop may be incorrect! 
  for (int i = 0; i < 4; i++){
    bool _days[7];
    for (int j = 0; j<7; j++)
    _days[j] = json[key][i]["days"][j].as<bool>();
    // TODO
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
}

// String name, int id, int pinName, Status status, bool timer, bool timerOnState, bool timerOffState, TypeStatus typeState,
//                        int timerOn, int timerOff, Repeat repeat, bool *days