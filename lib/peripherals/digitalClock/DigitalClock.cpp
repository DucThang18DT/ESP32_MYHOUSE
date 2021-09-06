#include "DigitalClock.h"  

DigitalClock::DigitalClock(){
   // DClock.begin();
  // DClock.setTimeOffset(+7*60*60);
  DateTime.setTimeZone("<+07>-7");
  DateTime.begin();
  if (!DateTime.isTimeValid()) {
    Serial.println("\n(DigitalClock) Failed to get time from server.");
  }
}

void DigitalClock::display(int pin, int Num){
  shiftOut(DATA, CLK, MSBFIRST, _seg7AnodeNum[Num]);
  shiftOut(DATA, CLK, MSBFIRST, _seg7Pin[pin]);
  digitalWrite(LAT, HIGH);
  digitalWrite(LAT, LOW);
  delay(80);
}

String DigitalClock::timeNow(){
  String tNow = DateTime.toString();
  int index = 1;
  for (int i = 0; i< 6; i++){
    String tmp = ""; 
    tmp += (tNow[++index] + tNow[++index]);
    _timeNow[i] = tmp.toInt();
    ++index;
  }
  return tNow;
}

void DigitalClock::_showTime(int index){
  timeNow();
  for (int i = 0; i < 6; i++){
    display(i, (i%2==0)?_timeNow[index]/10:_timeNow[index]%10);
    if (i%2 !=0) ++index;
  }
}

void DigitalClock::showTimeNow(){
  _showTime(3);
}

void DigitalClock::showDate(){
  _showTime(0);
}

int DigitalClock::getHours(){
  timeNow();
  return _timeNow[3];
}

int DigitalClock::getMinutes(){
  timeNow();
  return _timeNow[4];
}

int DigitalClock::getSeconds(){
  timeNow();
  return _timeNow[5];
}

int DigitalClock::getYear(){
  timeNow();
  return _timeNow[0];
}

int DigitalClock::getMonth(){
  timeNow();
  return _timeNow[1];
}

int DigitalClock::getDate(){
  timeNow();
  return _timeNow[2];
}

