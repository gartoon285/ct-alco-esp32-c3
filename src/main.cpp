#include <main.h>
void setup(){
  Serial.begin(115200);
  IO.initPins();
  IO.initSleep();
  ble.begin(BLE_Name);
  Wire.begin(i2c_SDA,i2c_SCL);
  Disp.init();
  IO.PWR5VOn();
  sensor.sgp30Init();
  fileS.init();
  Disp.DisplayWormUp();
  Disp.OLEDclear();

}
void loop(){
        sleepFn();
        ble.ButtonDisconnected();
        command();
        sensorUpdate();
}
