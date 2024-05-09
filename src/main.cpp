// #include <main.h>
// Alcohol alco;
// TickTask sensorUpdate(500);
// TickTask BLEconected(1000);
// // MyBLEService ble;
// void setup() {
//   Serial.begin(115200);
//   Wire.begin(i2c_SDA,i2c_SCL);
//   // ble.begin("Alcohol");
//   //pinMode(BUTTON,INPUT);
//   //pinMode(BUZZER,OUTPUT);
//   alco.mq3Init();
//   alco.mq3Cal();
//   delay(3000);
  
// }
// double alcoholPPM=0;
// void loop() {
//       if(sensorUpdate.Update()){// sampling frequency
//         alcoholPPM = alco.readMQ3(1);// 0 turn off Serial port debug; 1 turn on Serial port debug;
//         Serial.print("Alcohol now (PPM): ");
//         Serial.println(alcoholPPM);
        
//       }
// }
#include <main.h>

std::array<String,100> text;
MyBLEService ble;
FileSystem fileS;
EspSleep esp;
void setup(){
  Serial.begin(115200);
  esp.init();
  fileS.init();
  ble.begin("TEST");
    // fileS.Print("20 10 50",99,30.2,0b01110001);
  text=fileS.Read();
        if(ble.BleConnected()){
          ble.setState(text[0].c_str());
          Serial.println("Connected");
        }else{
        Serial.println("Disconnected");
        }
        for(int i=0;i<100;i++){
            Serial.println(text[i]);
        }
}
void loop(){
        esp.ButtonSleep(3);
  text=fileS.Read();
        if(ble.BleConnected()){
          ble.setLog(text[0].c_str());
          Serial.println("Connected");
        }else{
        Serial.println("Disconnected");
        }
        String s = ble.getRx();
        if(!s.isEmpty()){
        Serial.println(s);
        }
        delay(500);
}
// #include <main.h>

// Alcodisplay display;

// void setup(){
//   display.init();
//   Serial.begin(115200);
// }
// void loop(){
// Serial.println(display.randLED());
//   display.drawstyles("15.3");
//   delay(5000);
// }