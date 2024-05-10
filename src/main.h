#include <Alcohol.h>
#include <BLE_lib.h>
#include <Arduino.h>
#include <Wire.h>
#include <alcohol.h>
#include <battery_path.h>
#include <file_system.h>
#include <alcodisplay.h>
#include <hardware_io.h>
#define i2c_SDA 4
#define i2c_SCL 5
#define BLE_Name ("Alcohol")
#define Sleeptime 5 * 60
#define pressTime 3
#define LightSleep 2 * 60 * 1000
std::array<String, 100> text;
MyBLEService ble;
FileSystem fileS;
EspHardwareIo IO;
TickTask Sleep(Sleeptime * 1000);
Alcodisplay Disp;
Alcohol sensor;
// Voltage_max = 3.205
// R1=5.6K, R2=10k
// #define BUZZER 6
void setup();
void loop();
void sleepFn()
{
    if (IO.ButtonSleep(pressTime))
    {
        Sleep.clear();
        IO.PWR5VOn();
    }
    if (Sleep.Update())
    {
        esp_deep_sleep_start();
    }
    if (Sleep.getTick() >= LightSleep)
    {
        IO.PWR5VOff();
    }
}
void command()
{
    String json = ble.getRx();
    if (!json.isEmpty())
    {
        StaticJsonDocument<192> doc;
        DeserializationError error = deserializeJson(doc, json);
        if (error)
        {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.c_str());
            return;
        }
        String timestamp = doc[String("timestamp")];
        Serial.print("Timestamp: ");
        Serial.println(timestamp);
        String cmd = doc[String("cmd")];
        Serial.print("Command: ");
        Serial.println(cmd);
        int force = doc["fw_update"]["force"];
        Serial.print("Force Firmware Update: ");
        Serial.println(force);
        String fw_ver = doc["fw_update"][String("fw_ver")];
        Serial.print("Firmware Version: ");
        Serial.println(fw_ver);
    }
}
void sensorUpdate(){
    if(sensor.sgp30Update()){
        Disp.drawstyles(String(sensor.sgp30getCo2()),String(sensor.sgp30getEthanol()));
    }
}