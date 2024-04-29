#include <main.h>
Alcohol alco;
TickTask sensorUpdate(500);
TickTask BLEconected(1000);
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// MyBLEService ble;
void setup() {
  Serial.begin(115200);
  // Wire.begin(i2c_SDA,i2c_SCL);
  // ble.begin("Alcohol");
  // if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
  //   Serial.println(F("SSD1306 allocation failed"));
  //   for(;;); // Don't proceed, loop forever
  // }
  pinMode(BUTTON,INPUT);
  pinMode(BUZZER,OUTPUT);
  alco.mq3Init();
  alco.mq3Cal();
  // display.display();
  // delay(3000);
  // display.clearDisplay();
  // display.display();
}
double alcoholPPM=0;
void loop() {
      if(sensorUpdate.Update()){// sampling frequency
        alcoholPPM = alco.readMQ3(1);// 0 turn off Serial port debug; 1 turn on Serial port debug;
        Serial.print("Alcohol now (PPM): ");
        Serial.println(alcoholPPM);
        // drawstyles(String(alcoholPPM));
        
      }
      // if(BLEconected.Update()){
      //   if(ble.BleConnected()){
      //     ble.setSenseValue(alcoholPPM);
      //     Serial.println("Connected");
      //   }else{
      //   Serial.println("Disconnected");
      //   }
      // }
}
// void drawstyles(String text){
//   display.clearDisplay();
//   display.setTextSize(1.2);             // Normal 1:1 pixel scale
//   display.setTextColor(SSD1306_WHITE);        // Draw white text
//   display.setCursor(0,0);             // Start at top-left corner
//   display.println("Alcohol now (PPM)");
//   display.setTextSize(1);             // Normal 1:1 pixel scale
//   display.println(text);
//   display.display();
// }