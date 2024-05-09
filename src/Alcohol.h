#ifndef alcohol
#define alcohol
#include <MQUnifiedsensor.h>
#include <Wire.h>
#define ADC_BATT 2
#include "SGP30.h"

/************************Hardware Related Macros************************************/
#define Board ("ESP-32") // Wemos ESP-32 or other board, whatever have ESP32 core.
#define Pin (3)          // IO25 for your ESP32 WeMos Board, pinout here: https://i.pinimg.com/originals/66/9a/61/669a618d9435c702f4b67e12c40a11b8.jpg
/***********************Software Related Macros************************************/
#define Type ("MQ-3")              // MQ3 or other MQ Sensor, if change this verify your a and b values.
#define Voltage_Resolution (3.3) // 3V3 <- IMPORTANT. Source: https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
#define ADC_Bit_Resolution (12)    // ESP-32 bit resolution. Source: https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
#define RatioMQ3CleanAir (60)      // Ratio of your sensor, for this example an MQ-3
                                   /*****************************Globals***********************************************/

class Alcohol
{
public:
  void print_battery();
  void sgp30Init();
  void mq3Init();
  void mq3Cal();
  bool sgp30Update();
  float sgp30getEthanol();
  float sgp30getCo2();
  double readMQ3(bool debug);

private:
  double mapd(double x, double in_min, double in_max, double out_min, double out_max);
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
};
#endif