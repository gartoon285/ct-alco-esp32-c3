#define i2c_SDA 4
#define i2c_SCL 5
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3c ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#include <Alcohol.h>
#include <BLE_lib.h>
#include <Arduino.h>
#include <Wire.h>
#include <alcohol.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//Voltage_max = 3.205
//R1=5.6K, R2=10k
#define BUTTON 10
#define BUZZER 6
#define OLED_RESET -1
void setup();
void loop();
void drawstyles(String text);