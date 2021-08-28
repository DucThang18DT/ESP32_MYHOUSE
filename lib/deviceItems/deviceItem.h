#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <vector>

// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP);

enum TypeStatus{OnOff, OpenClose};
enum Repeat{Once, Everyday, Option};
enum Status{ON, OFF, OPEN, CLOSE};

class DeviceItem{
  private:
    String _name;
    int _id;
    int _pinName;
    Status _state;
    bool _timer;
    bool _timerOnState;
    bool _timerOffState;
    TypeStatus _typeState;
    int _timerOn;
    int _timerOff;
    Repeat _repeat;
    bool _days[7];

    bool checkTimer(int, bool);
  
  public:

    // getter
    int pinName(){return _pinName;}
    int id(){return _id;}
    String name(){return _name;}
    TypeStatus typeState(){return _typeState;}
    Status status(){return _state;}
    Repeat repeat(){return _repeat;}
    int timerOn(){return _timerOn;}
    int timerOff(){return _timerOff;}
    bool timerOnState(){return _timerOnState;}
    bool timerOffState(){return _timerOffState;}
    bool timer(){return _timer;}
    bool* days(){return _days;}
    bool day(int index){return _days[index];}

    // setter
    void newName(String name = "NoName"){_name = name;}
    void newRepeat(Repeat repeat = Repeat::Once){_repeat = repeat;}
    void newId(int id = 0){_id = id;}
    void newDay(int, bool);
    void newDays(bool*); 
    void newPinName(int pinName = 0){_pinName = pinName;}
    void newTypeState(TypeStatus);
    void newState(Status);
    void newTimerOn(int time = -1){_timerOn = time;}
    void newTimerOff(int time = -1){_timerOff = time;}
    void newTimerOnState(bool state = false){_timerOnState = state;}
    void newTImerOffState(bool state = false){_timerOffState = state;}
    void newTimer(bool timer = false){_timer = timer;}

    // Constructor
    DeviceItem(){} 
    DeviceItem(String, int, int);
    DeviceItem(String, int, int, Status, bool, bool, bool, TypeStatus, int, int, Repeat, bool*);

    // Destructor
    ~DeviceItem(){}


    void changeState();
    void turnOff();
    void setTimerOn(int, int);
    void setTimerOff(int, int);
    int getHourOn();
    int getMinuteOn();
    int getHourOff();
    int getMinuteOff();

    // TODO
    bool isTimeToOn();
    bool isTimeToOff();


    // static void buildListObjects(std::vector<DeviceItem>* , String, String);
    static void addObject(std::vector<DeviceItem>*, String);
    static void updateObject(std::vector<DeviceItem>*, int, String);
    static String buildJson(std::vector<DeviceItem>*, String);
    String toJson();
};

#endif