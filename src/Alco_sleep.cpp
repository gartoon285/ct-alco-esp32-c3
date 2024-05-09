#include <Alco_sleep.h>

void EspSleep::init()
{
    pressB =0;
    pinMode(INTERRUPT_PIN, INPUT_PULLUP);
    esp_deep_sleep_enable_gpio_wakeup(1 << INTERRUPT_PIN,
                                      ESP_GPIO_WAKEUP_GPIO_LOW);
    if (digitalRead(INTERRUPT_PIN) == LOW)
    {
        unsigned long pressB = millis();
        while (digitalRead(INTERRUPT_PIN) == LOW)
        {
            if (millis() - pressB >= 3000)
            {
                break;
            }
        }
        if (millis() - pressB >= 3000)
        {
            Serial.println("System On");
        }
        else
        {
            Serial.println("Going to sleep now");
            esp_deep_sleep_start();
        }
    }
    else if (digitalRead(INTERRUPT_PIN) == HIGH)
    {
        Serial.println("Going to sleep now");
        esp_deep_sleep_start();
    }
}
void EspSleep::ButtonSleep(int t)
{
    if (digitalRead(INTERRUPT_PIN) == LOW)
    {
        if (pressB == 0)
        {
            pressB = millis();
        }
        if (millis() - pressB >= t * 1000)
        {
            Serial.println("Going to sleep now");
            esp_deep_sleep_start();
        }
    }
    else
    {
        pressB = 0;
    }
}