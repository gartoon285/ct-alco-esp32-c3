// MyBLELibrary.h

#ifndef BLE_lib
#define BLE_lib

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Arduino.h>
#include <SPI.h>

#define Sensor_UUID        "5d5da583-a4f5-44ca-8afe-d7bc7eb7d217"
#define Sensor_CHARACTERISTIC_UUID "1cbcd468-5923-4bac-8d06-820b1c3e743d"

#define Batt_UUID "0000180f-0000-1000-8000-00805f9b34fb"
#define BattState_Characteristic_UUID "00002a1a-0000-1000-8000-00805f9b34fb"
#define Battlevel_Characteristic_UUID "00002a19-0000-1000-8000-00805f9b34fb"

class MyBLEService {
  public:
    void begin(String s);
    void setSenseValue(int value);
    void setBattLevel(u8_t level);
    void setBattState(bool State);
    bool BleConnected();
  private:
    BLEServer *pServer;
    BLEService *sensorService;
    BLECharacteristic *SensorCharacteristic;

    BLEService *battService;
    BLECharacteristic *battLevelCharacteristic;
    BLECharacteristic *battStateCharacteristic;
};


#endif
