// MyBLELibrary.h

#ifndef BLE_lib
#define BLE_lib

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Arduino.h>
#include <SPI.h>

#define Log_UUID        "5d5da583-a4f5-44ca-8afe-d7bc7eb7d217"
#define Log_CHARACTERISTIC_UUID "1cbcd468-5923-4bac-8d06-820b1c3e743d"

#define TxRx_UUID "61ced631-7ddf-44f0-80f7-ecffe3a1656b"
#define Tx_Characteristic_UUID "9d7dc8bc-04d5-4c20-8c01-4d4ca28bab51"
#define Rx_Characteristic_UUID "4de68642-2eca-44e9-8f7e-06cdd936d0c3"
class MyBLEService {
  public:
    void begin(String s);
    void setLog(std::string log);
    void setState(std::string state);
    bool BleConnected();
    String getRx();
  private:
    BLEServer *pServer;
    BLEService *LogService;
    BLECharacteristic *LogCharacteristic;

    BLEService *TxRxService;
    BLECharacteristic *TxCharacteristic;
    BLECharacteristic *RxCharacteristic;
};


#endif
