#ifndef _MYTASK_H_
#define _MYTASK_H_

    #include <DeviceItem.h>
    #include <FBRtDatabase.h>
    #include <fbInter/FBRtInteraction.h>
    #include <myWifi/myWifi.h>
    #include <digitalClock/DigitalClock.h>
    #include <tempAndHum/TempAndHum.h>

    static TaskHandle_t Task2;
    static TaskHandle_t Task3;

    static unsigned long referenceTime2;
    static unsigned long referenceTime3;

    void alarm(void *);
    void dhtData(void *);

#endif