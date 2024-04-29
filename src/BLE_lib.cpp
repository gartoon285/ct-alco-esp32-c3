// MyBLELibrary.cpp

#include <BLE_lib.h>

bool deviceConnected =false;
bool oldDeviceConnected = false;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void MyBLEService::begin(String s) {
  BLEDevice::init(s.c_str());
  BLEDevice::setPower(ESP_PWR_LVL_N12);
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  sensorService = pServer->createService(Sensor_UUID);
  SensorCharacteristic = sensorService->createCharacteristic(
                        Sensor_CHARACTERISTIC_UUID,
                        BLECharacteristic::PROPERTY_NOTIFY
                    );
  battService =  pServer->createService(Batt_UUID);
  battLevelCharacteristic =battService->createCharacteristic(
                        Battlevel_Characteristic_UUID,
                        BLECharacteristic::PROPERTY_NOTIFY
                    );
  battStateCharacteristic =battService->createCharacteristic(
                        BLEUUID((uint16_t)0x2A1A),
                        BLECharacteristic::PROPERTY_NOTIFY
                    );
  
  SensorCharacteristic->addDescriptor(new BLE2902());
  battLevelCharacteristic->addDescriptor(new BLE2902());
  battStateCharacteristic->addDescriptor(new BLE2902());
  sensorService->start();
  battService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

void MyBLEService::setSenseValue(std::string value){
    SensorCharacteristic->setValue(value);
    SensorCharacteristic->notify();
}
void MyBLEService::setBattLevel(u8_t level){
    battLevelCharacteristic->setValue(&level,1);
    battLevelCharacteristic->notify();
}
void MyBLEService::setBattState(bool State){
    uint8_t data_chg;
    if(State == 1){
        data_chg = 0x75;
    }
    else
    {
        data_chg = 0x65;
    }
    battStateCharacteristic->setValue(&data_chg,1);
    battStateCharacteristic->notify();
}
bool MyBLEService::BleConnected(){
     bool State = false;
     if (deviceConnected) {
        State = true;
	}

    // disconnecting
    else if (!deviceConnected && oldDeviceConnected) {
        pServer->startAdvertising(); // restart advertising
        oldDeviceConnected = deviceConnected;
        State = false;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        oldDeviceConnected = deviceConnected;
        State = true;
    }
    return State;
}
