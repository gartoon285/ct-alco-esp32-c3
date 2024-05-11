#ifndef hardware
#define hardware

#include "Arduino.h"
#include <SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h>

#define PWR_5V 6
#define LED_BLE 1

#define LED_CHG 8
#define SW_BLE 10
#define SW_PWR_KEY 2
#define BUZZER 19

#define TimeDelay 500

#define pressTime 3
#define Sleeptime 5 * 60
#define LightSleep 2 * 60 * 1000

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
    void sleepFn();
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
/**************************** IP5306 I2C Register ********************************************/
#define _i2c_5306Address 0xea
#define _i2c_charge_register 0x70
#define _i2c_chargeState_register 0x71
#define _i2c_SYS_CTL0_register 0x00
#define _i2c_SYS_CTL1_register 0x01
#define _i2c_SYS_CTL2_register 0x02
class Battery
{
public:
  void max17048Init();
  double getVoltage();
  double getSoc();
  bool getAlert();
  bool getCharge_en();
  bool getChargeState();
  void ip5306Init();
  int8_t getBatteryLevel();

private:
  double voltage = 0; // Variable to keep track of LiPo voltage
  double soc = 0;     // Variable to keep track of LiPo state-of-charge (SOC)
  bool alert;
  bool charge_en;
  bool chargeState;
};
#endif