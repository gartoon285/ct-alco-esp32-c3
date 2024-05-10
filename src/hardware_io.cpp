#include <hardware_io.h>

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