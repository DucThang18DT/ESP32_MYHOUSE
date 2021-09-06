#ifndef _MYTASK_H_
#define _MYTASK_H_

    TaskHandle_t Task2;
    TaskHandle_t Task3;

    unsigned long referenceTime2;
    unsigned long referenceTime3;

    void alarm(void *);
    void dhtData(void *);

#endif