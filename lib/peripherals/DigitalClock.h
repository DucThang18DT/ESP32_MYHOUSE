#ifndef _DIGITALCLOCK_H_
#define _DIGITALCLOCK_H_

    #include <NTPClient.h>
    #include <WiFiUdp.h>
    #include <Arduino.h>

    WiFiUDP NtpUDP;
    NTPClient DClock(NtpUDP);
  
    class DigitalClock
    {
    private:
        int _seg7Anode[12] = {0x88, 0xBD, 0xC4, 0xA4, 0xB1, 0xA2, 0x82, 0xBC, 0x80, 0xA0, 0xF0, 0xCA};
        int _seg7Pin[5] = {23 , 24 , 25, 26, 27};
    public:
        void display(int, int);
        String timeNow();
        DigitalClock(/* args */);
        ~DigitalClock();
    };
    
#endif