#include <BLE_lib.h>
#include <Arduino.h>
#include <Wire.h>
#include <file_system.h>
#include <hardware_io.h>
#define i2c_SDA 4
#define i2c_SCL 5
#define BLE_Name ("Alcohol")

std::array<String, 100> text;
MyBLEService ble;
FileSystem fileS;
EspHardwareIo IO;
// Voltage_max = 3.205
// R1=5.6K, R2=10k
void setup();
void loop();

