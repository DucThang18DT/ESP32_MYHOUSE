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

// Not used - use addObject instead.
// void DeviceItem::buildListObjects(std::vector<DeviceItem> listItems[], String jsonString, String key =""){
//   Serial.printf("\n(DeviceItem::Build list object) size of listDevice = %d\n", listItems->size());
//   while (listItems->size() > 0) listItems->pop_back();
//   listItems->resize(0);
//   Serial.printf("\n(DeviceItem::Build list object) size of listDevice after = %d\n", listItems->size());
//   Serial.printf("\n(DeviceItem::Build list object) capacity of listDevice after = %d\n", listItems->capacity());
//   Serial.printf("\n(DeviceItem::Build list object) key = %s\n", key.c_str());
//   DynamicJsonDocument json(1024*100);
//   // problem
//   /*
//   Guru Meditation Error: Core  1 panic'ed (LoadProhibited). Exception was unhandled.
// Core 1 register dump:
// PC      : 0x400eb8b6  PS      : 0x00060330  A0      : 0x800f28fd  A1      : 0x3fff5600  
// A2      : 0x00000000  A3      : 0x3fff57f4  A4      : 0x00000000  A5      : 0x00000000
// A6      : 0x3fff59e0  A7      : 0x00000008  A8      : 0x3fff5910  A9      : 0x3fff55f0  
// A10     : 0x3fff5610  A11     : 0x3ff9c510  A12     : 0x000000ff  A13     : 0x0000ff00  
// A14     : 0x00ff0000  A15     : 0xff000000  SAR     : 0x00000010  EXCCAUSE: 0x0000001c
// EXCVADDR: 0x00000000  LBEG    : 0x400014fd  LEND    : 0x4000150d  LCOUNT  : 0xffffffff  

// ELF file SHA256: 0000000000000000

// Backtrace: 0x400eb8b6:0x3fff5600 0x400f28fa:0x3fff5910 0x400f2932:0x3fff59a0 0x400e6e72:0x3fff59e0 0x400e339e:0x3fff5a80 0x400e6531:0x3fff62f0 0x400d1d39:0x3fff6340 0x400d78c5:0x3fff63c0 0x400da9dd:0x3fff64b0 0x400db047:0x3fff6770 0x400db2f5:0x3fff6790 0x400db34d:0x3fff6830 0x400db414:0x3fff6850 0x40089ab2:0x3fff6870
//   */
//   // json->clear();
//   deserializeJson(json, jsonString);
//   json.shrinkToFit();
//   Serial.printf("\n(DeviceItem::build list object) json size: %d", json.size());
//   Serial.printf("\nJson: ");
//   // Serial.printf(json[key][0]["name"]);
//   // Serial.println("\nlistDevices: ");
//   // for (int i = 0; i < *json["length"]->as<int>(); i++){
//   //   bool _days[7];
//   //   for (int j = 0; j<7; j++)
//   //   {_days[j] = json[key][i]["days"][j].as<bool>();
//   //   Serial.printf("\n(DeviceItem::buildlistObject) _days[%d] : ",j);
//   //   Serial.println(_days[j]);}
//   //   listItems->push_back(DeviceItem(
//   //     json[key][i]["name"].as<String>(),
//   //     json[key][i]["id"].as<int>(),
//   //     json[key][i]["pinName"].as<int>(),
//   //     (json[key][i]["status"].as<int>() == 1)? Status::ON:Status::OFF,
//   //     json[key][i]["timer"].as<bool>(),
//   //     json[key][i]["timerOnState"].as<bool>(),
//   //     json[key][i]["timerOffState"].as<bool>(),
//   //     (json[key][i]["typeState"].as<int>() == 1)? TypeStatus::OnOff:TypeStatus::OpenClose,
//   //     json[key][i]["timerOn"].as<int>(),
//   //     json[key][i]["timerOff"].as<int>(),
//   //     (json[key][i]["repeat"].as<int>() == 0) ? Repeat::Once :(json[key][i]["repeat"].as<int>() == 1 ? Repeat::Everyday:Repeat::Option),
//   //     _days
//   //   ));
//   //   Serial.println(listItems->at(i).name());
//   // }
//   Serial.printf("\n(DeviceItem::build list object) json size: %d", json.size());
//   Serial.printf("\n(DeviceItem::build list object) list size: %d", listItems->size());
//   // json.remove(key);
//   // json.remove("users");
//   // json.remove("length");
//   // json.clear();
//   Serial.printf("\n(DeviceItem::build list object) json size affter: %d", json.size());
//   Serial.println("\n(DeviceItem::Build list object) Complete build list devices");
// }

void DeviceItem::addObject(std::vector<DeviceItem> listItems[], String jsonString){
  DynamicJsonDocument json(1024);
  deserializeJson(json, jsonString);
  json.shrinkToFit();
  // Serial.printf("\n(DeviceItem::addObject) json size: %d", json.size());
  // Serial.printf("\n(DeviceItem::addObject) Devices: ");
  // Serial.printf(json["name"]);
  
  bool _days[7];
  for (int j = 0; j<7; j++){
    _days[j] = json["days"][j].as<bool>();
    // Serial.printf("\n(DeviceItem::addObject) _days[%d] : ",j);
    // Serial.println(_days[j]);
    }

  listItems->push_back(DeviceItem(
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
  ));

  // Serial.printf("\n(DeviceItem::addObject) json size: %d", json.size());
  // Serial.printf("\n(DeviceItem::addObject) list size: %d", listItems->size());
  json.clear();
  // Serial.printf("\n(DeviceItem::addObject) json size affter: %d", json.size());
  Serial.println("\n(DeviceItem::addObject) Complete build list devices\n");
}

void DeviceItem::updateObject(std::vector<DeviceItem> listItems[], int index, String jsonString){
  // Serial.printf("(DeviceItem::update Object) list size: %d", (listItems)->size());
  DynamicJsonDocument json(1024);
  deserializeJson(json, jsonString);
  Serial.printf("\n(DeviceItem::update Object) Update device: ");
  Serial.printf(json["name"]);
  Serial.println("\n(DeviceItem::update Object) Device index: ");
  Serial.println(index);

  bool _days[7];
  for (int j = 0; j<7; j++)
  _days[j] = json["days"][j].as<bool>();
  // Serial.println("(DeviceItem::update Object) start update");

  listItems->at(index).newName(json["name"].as<String>());
  // Serial.println("update OK");
  listItems->at(index).newId(json["id"].as<int>());
  // Serial.println("update OK");
  listItems->at(index).newPinName(json["pinName"].as<int>());
  // Serial.println("update OK");
  listItems->at(index).newState((json["status"].as<int>() == 1)? Status::ON:Status::OFF);
  // Serial.println("update OK");
  listItems->at(index).newTimer(json["timer"].as<bool>());
  // Serial.println("update OK");
  listItems->at(index).newTimerOnState(json["timerOnState"].as<bool>());
  // Serial.println("update OK");
  listItems->at(index).newTImerOffState(json["timerOffState"].as<bool>());
  // Serial.println("update OK");
  listItems->at(index).newTypeState((json["typeState"].as<int>() == 1)? TypeStatus::OnOff:TypeStatus::OpenClose);
  // Serial.println("update OK");
  listItems->at(index).newTimerOn(json["timerOn"].as<int>());
  // Serial.println("update OK");
  listItems->at(index).newTimerOff(json["timerOff"].as<int>());
  // Serial.println("update OK");
  listItems->at(index).newRepeat((json["repeat"].as<int>() == 0) ? Repeat::Once :(json["repeat"].as<int>() == 1 ? Repeat::Everyday:Repeat::Option));
  // Serial.println("update OK");
  listItems->at(index).newDays(_days);
  // Serial.println("update OK");
  
  Serial.println(listItems->at(index).name());
  Serial.println("\n(DeviceItem::update Object) Complete update object");
}

String DeviceItem::buildJson(std::vector<DeviceItem> listItems[], String key = ""){
  // Serial.printf("\n(DeviceItem::buildJson) list Size: ");
  // Serial.println(listItems->size());
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
  // Serial.println("\n(DeviceItem::build Json) Json String: \n" + jsonString);
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
  // Serial.println("\n(DeviceItem::toJson) Json String: \n" + jsonString);
  return jsonString;
}

bool DeviceItem::isTimeToOn(){
  if (timer() && timerOnState())
    return checkTimer(timerOn(), true);
  return false;
}

bool DeviceItem::isTimeToOff(){
  if (timer() && timerOffState()) 
    return checkTimer(timerOff(), false);
  return false;
}

// Check timerOn and timerOff
// mode = true -> Check timerOn
// mode = false -> Check timerOff
bool DeviceItem::checkTimer(int time, bool mode){
  WiFiUDP ntpUDP;
  NTPClient timeClient(ntpUDP);

  timeClient.begin();
  timeClient.setTimeOffset(+7*60*60);
  while(!timeClient.update()) 
    timeClient.forceUpdate();

  int timeNow = timeClient.getHours()*3600 + timeClient.getMinutes()*60 + timeClient.getSeconds();
  // Serial.printf("\n(DeviceItem::checkTimer) Time now: %d:%d:%d\n", timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds());
  // Serial.printf("\n(DeviceItem::checkTimer) Time now in second: %d", timeNow);
  switch (repeat())
  {
  case Repeat::Once:
    if ((timeNow - time >= 0) && (timeNow - time <=  15)) {
      if (mode){
        newState(Status::ON);
        newTimerOnState(false);}
      else {
        newState(Status::OFF);
        newTImerOffState(false);
      }
      return true;
      }      
    break;
  case Repeat::Everyday:
    if ((timeNow - time >= 0) && (timeNow - time <=  15)) {
      if (mode) newState(Status::ON);
      else newState(Status::OFF);
      return true;}
    break;
  case Repeat::Option:
    if (day(timeClient.getDay()))
      if ((timeNow - time >= 0) && (timeNow - time <=  15)) {
        if (mode) newState(Status::ON);
        else newState(Status::OFF);
        return true;}
    break;
  }
  return false;
}