// MyBLELibrary.cpp

#include <BLE_lib.h>
#include <hardware_io.h>
String data;
bool deviceConnected =false;
bool oldDeviceConnected = false;
EspHardwareIo esp;
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};
class MyCallbacks: public BLECharacteristicCallbacks {
  public:
     void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
      data = String(rxValue.c_str());
    }
};

void MyBLEService::begin(String s) {
  BLEDevice::init(s.c_str());
  BLEDevice::setPower(ESP_PWR_LVL_N12);
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  LogService = pServer->createService(Log_UUID);
  LogCharacteristic = LogService->createCharacteristic(
                        Log_CHARACTERISTIC_UUID,
                        BLECharacteristic::PROPERTY_NOTIFY
                    );
  TxRxService =  pServer->createService(TxRx_UUID);
  TxCharacteristic =TxRxService->createCharacteristic(
                        Tx_Characteristic_UUID,
                        BLECharacteristic::PROPERTY_NOTIFY
                    );
  RxCharacteristic =TxRxService->createCharacteristic(
                        Rx_Characteristic_UUID,
                        BLECharacteristic::PROPERTY_WRITE
                    );
  
  LogCharacteristic->addDescriptor(new BLE2902());
  TxCharacteristic->addDescriptor(new BLE2902());
  RxCharacteristic->setCallbacks(new MyCallbacks());
  LogService->start();
  TxRxService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

void MyBLEService::setLog(std::string log){
    LogCharacteristic->setValue(log);
    LogCharacteristic->notify();
}
void MyBLEService::setState(std::string state){
    TxCharacteristic->setValue(state);
    TxCharacteristic->notify();
}
String MyBLEService:: getRx(){
  String s = data;
  data="";
  return s;
}
bool MyBLEService::BleConnected(){
     bool State = false;
     if (deviceConnected) {
        State = true;
      esp.BleLedOn();
	}

    // disconnecting
    else if (!deviceConnected && oldDeviceConnected) {
        pServer->startAdvertising(); // restart advertising
        oldDeviceConnected = deviceConnected;
        State = false;
        esp.BleLedBlink();
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        oldDeviceConnected = deviceConnected;
        State = true;
        esp.BleLedOn();
    }
    return State;
}
void MyBLEService::ButtonDisconnected(){
  if (digitalRead(SW_BLE) == LOW)
    {
        if (pressButtonBle == 0)
        {
            pressButtonBle = millis();
        }
        if (millis() - pressButtonBle >= TimePress * 1000)
        {
            pServer->disconnect(0);
        }
    }
    else
    {
        pressButtonBle = 0;
    }
}