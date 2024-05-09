#define i2c_SDA 6
#define i2c_SCL 5
#include <Alcohol.h>
#include <BLE_lib.h>
#include <Arduino.h>
#include <Wire.h>
#include <alcohol.h>
#include <battery_path.h>
#include <file_system.h>
#include <alcodisplay.h>
#include <ArduinoJson.h>
#include <Alco_sleep.h>
//Voltage_max = 3.205
//R1=5.6K, R2=10k
#define BUTTON 10
//#define BUZZER 6
void setup();
void loop();