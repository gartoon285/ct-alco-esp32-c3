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
  fs.init();
  pAdvertising->start();
}

void MyBLEService::setLog(){
    std::array<String, 100> messages=fs.Read();
    for(int i=0;i<100;i++){
    if(!messages[i].isEmpty()){
    LogCharacteristic->setValue(messages[i].c_str());
    LogCharacteristic->notify();
    }
    }
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
void MyBLEService ::command()
{
    String json = getRx();
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