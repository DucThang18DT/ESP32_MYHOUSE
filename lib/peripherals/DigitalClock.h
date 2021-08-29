#ifndef _DIGITALCLOCK_H_
#define _DIGITALCLOCK_H_

    // #include <NTPClient.h>
    // #include <WiFiUdp.h>
    #include <Arduino.h>
    #include <ESPDateTime.h>

    // static WiFiUDP NtpUDP;
    // static NTPClient DClock(NtpUDP);
    
    // 3 pins of IC 74HC595
    #define CLK     32
    #define DATA    35
    #define LAT     34

    class DigitalClock
    {
    private:
        int _seg7AnodeNum[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
        int _seg7Pin[6] = {0,1,2,3,4,5};
        int _timeNow[6] = {0,0,0,0,0,0};

        void _showTime(int);
    public:
        void display(int, int);
        void showTimeNow();
        void showDate();
        String timeNow();

        // getter
        int getHours();
        int getMinutes();
        int getSeconds();
        int getDate();
        int getMonth();
        int getYear();

        DigitalClock();
        ~DigitalClock(){}
    };
    
#endif