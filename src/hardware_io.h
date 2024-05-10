#ifndef hardware
#define hardware

#define PWR_5V 18
#define LED_BLE 1

#define LED_CHG 8
#define SW_BLE 10
#define SW_PWR_KEY 2
#define BUZZER 19

#define TimeDelay 500
#include "Arduino.h"

class EspHardwareIo
{
public:
    void initSleep();
    void initPins();
    bool ButtonSleep(int t);
    void BleLedOn();
    void BleLedOff();
    void BleLedBlink();
    void PWR5VOn();
    void PWR5VOff();
    void BuzzerOn();
    void BuzzerOff();
    void LedChgOn();
    void LedChgOff();
private:
    unsigned long pressButtonPWR = 0;
    bool LEDState=false;
    unsigned long millisdelay=0;
};
class TickTask
{
    unsigned long Millis_t;
    unsigned long MillisDelay;
    unsigned long MillisCount;

public:
    TickTask(unsigned long milDelay);
    bool Update();
    unsigned long getTick();
    void clear();
};
#endif