#include <hardware_io.h>
TickTask Sleep(Sleeptime * 1000);
void EspHardwareIo::initSleep()
{   
    pinMode(SW_PWR_KEY,INPUT_PULLUP);
    pressButtonPWR = 0;
    esp_deep_sleep_enable_gpio_wakeup(1 << SW_PWR_KEY,
                                      ESP_GPIO_WAKEUP_GPIO_LOW);
    if (digitalRead(SW_PWR_KEY) == LOW)
    {
        pressButtonPWR = millis();
        while (digitalRead(SW_PWR_KEY) == LOW)
        {
            if (millis() - pressButtonPWR >= 3000)
            {
                Serial.println("Break");
                break;
            }
        }
        if (millis() - pressButtonPWR >= 3000)
        {
            Serial.println("System On");
        }
        else
        {
            Serial.println("Going to sleep now");
            esp_deep_sleep_start();
        }
    }
    else if (digitalRead(SW_PWR_KEY) == HIGH)
    {
        Serial.println("Going to sleep now");
        esp_deep_sleep_start();
    }
}
bool EspHardwareIo::ButtonSleep(int t)
{
    bool State;
    if (digitalRead(SW_PWR_KEY) == LOW)
    {
        State = true;
        if (pressButtonPWR == 0)
        {
            pressButtonPWR = millis();
        }
        if (millis() - pressButtonPWR >= t * 1000)
        {
            Serial.println("Going to sleep now");
            esp_deep_sleep_start();
        }
    }
    else
    {
        pressButtonPWR = 0;
        State = false;
    }
    return State;
}
void EspHardwareIo::initPins()
{
    pinMode(PWR_5V,OUTPUT);
    pinMode(LED_BLE,OUTPUT);
    pinMode(LED_CHG,OUTPUT);
    pinMode(SW_BLE,INPUT_PULLUP);
    pinMode(BUZZER,OUTPUT);
}
void EspHardwareIo::BleLedOn(){
    digitalWrite(LED_BLE,1);
}
void EspHardwareIo::BleLedBlink(){
    if(millis() - millisdelay >= TimeDelay){
          LEDState=!LEDState;
          digitalWrite(LED_BLE,LEDState);
          millisdelay = millis();
        }
}
void EspHardwareIo::BleLedOff(){
    digitalWrite(LED_BLE,0);
}
void EspHardwareIo::PWR5VOn(){
    digitalWrite(PWR_5V,1);
}
void EspHardwareIo::PWR5VOff(){
    digitalWrite(PWR_5V,0);
}
void EspHardwareIo::LedChgOn(){
    digitalWrite(LED_CHG,1);
}
void EspHardwareIo::LedChgOff(){
    digitalWrite(LED_CHG,0);
}
void EspHardwareIo :: sleepFn()
{
    if (ButtonSleep(pressTime))
    {
        Sleep.clear();
        PWR5VOn();
    }
    if (Sleep.Update())
    {
        esp_deep_sleep_start();
    }
    if (Sleep.getTick() >= LightSleep)
    {
        PWR5VOff();
    }
}
/******************** TickTask *******************/
bool TickTask::Update()
{
    unsigned long currentMillis = millis();
    MillisCount = currentMillis - Millis_t;
    if (MillisCount >= MillisDelay)
    {
        Millis_t = currentMillis;
        return true;
    }
    else
        return false;
}

unsigned long TickTask::getTick()
{
    return MillisCount;
}

TickTask::TickTask(unsigned long milDelay)
{
    MillisDelay = milDelay;
}
void TickTask::clear()
{
    Millis_t = millis();
}
/*********************Power Path***************************************/
SFE_MAX1704X lipo(MAX1704X_MAX17048);
void Battery::max17048Init()
{
  // Set up the MAX17043 LiPo fuel gauge:
  if (lipo.begin() == false) // Connect to the MAX17043 using the default wire port
  {
    Serial.println(F("MAX17043 not detected. Please check wiring. Freezing."));
    while (1)
      ;
  }
  // Quick start restarts the MAX17043 in hopes of getting a more accurate
  // guess for the SOC.
  lipo.quickStart();
  // We can set an interrupt to alert when the battery SoC gets too low.
  // We can alert at anywhere between 1% - 32%:
  lipo.setThreshold(30); // Set alert threshold to 20%.

  /********************************Fuel Gauge Setup***********************************************/
}
double Battery ::getVoltage()
{
  voltage = lipo.getVoltage();
  return voltage;
}
double Battery ::getSoc()
{
  soc = lipo.getSOC();
  return soc;
}
bool Battery ::getAlert()
{
  alert = lipo.getAlert();
  return alert;
}
bool Battery ::getCharge_en()
{
  Wire.requestFrom(_i2c_5306Address, _i2c_charge_register);
  charge_en = Wire.read() >> 3;
  return charge_en;
}
bool Battery ::getChargeState()
{
  Wire.requestFrom(_i2c_5306Address, _i2c_chargeState_register);
  chargeState = Wire.read() >> 3;
  return chargeState;
}
void Battery::ip5306Init(){
    Wire.beginTransmission(_i2c_5306Address);
    Wire.write(_i2c_SYS_CTL0_register);
    Wire.write(0b10111110);
    Wire.endTransmission();
    Wire.beginTransmission(_i2c_5306Address);
    Wire.write(_i2c_SYS_CTL1_register);
    Wire.write(0b00000101);
    Wire.endTransmission();
    Wire.beginTransmission(_i2c_5306Address);
    Wire.write(_i2c_SYS_CTL2_register);
    Wire.write(0b00000000);
    Wire.endTransmission();
}
int8_t Battery:: getBatteryLevel()
{
  Wire.beginTransmission(_i2c_5306Address);
  Wire.write(0x78);
  if (Wire.endTransmission(false) == 0
   && Wire.requestFrom(0x75, 1)) {
    switch (Wire.read() & 0xF0) {
    case 0xE0: return 25;
    case 0xC0: return 50;
    case 0x80: return 75;
    case 0x00: return 100;
    default: return 0;
    }
  }
  return -1;
}