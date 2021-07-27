#include "DigitalClock.h"  

void DigitalClock::display(int pin, int Num){
  digitalWrite(_seg7Pin[pin], Num);
  delay(80);
}

String DigitalClock::timeNow(){
  while (!DClock.update())
    DClock.forceUpdate();
  String Time = DClock.getFormattedTime();
  int indexT = Time.indexOf("T");
  String Now = Time.substring(indexT+1, Time.length()-1);
  return Now;
}
