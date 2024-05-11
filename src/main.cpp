#include <main.h>
void setup(){
  Serial.begin(115200);
  IO.initPins();
  IO.initSleep();
  ble.begin(BLE_Name);
  Wire.begin(i2c_SDA,i2c_SCL);
  IO.PWR5VOn();
  fileS.init();

}
void loop(){
        IO.sleepFn();
        ble.ButtonDisconnected();
}
