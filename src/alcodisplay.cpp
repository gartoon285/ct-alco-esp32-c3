#include <alcodisplay.h>

Adafruit_SSD1306 Dis(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void Alcodisplay::init()
{
    if (!Dis.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }
    pixels.begin();
    Dis.display();
    Dis.clearDisplay();
    Dis.display();
    Dis.clearDisplay();
}

void Alcodisplay::drawstyles(String text)
{
    Dis.clearDisplay();
    Dis.setTextSize(1);              // Normal 1:1 pixel scale
    Dis.setTextColor(SSD1306_WHITE); // Draw white text
    Dis.setCursor(0, 0);             // Start at top-left corner
    Dis.println("Alcohol now (PPM)");
    Dis.setTextSize(1); // Normal 1:1 pixel scale
    Dis.println(text);
    Dis.display();
}

String Alcodisplay::randLED()
{
    pixels.clear();
    byte rand1 = random(0, 3);
    byte rand2 = random(4, 7);
    while(rand1 == rand1before && rand2 == rand2before){
        rand1 = random(0, 3);
    } 
    pixels.setPixelColor(rand1, pixels.Color(50, 0, 0));
    pixels.setPixelColor(rand2, pixels.Color(50, 0, 0));
    pixels.show();
    String rand3 = String((1 << rand1) | (1 << rand2), BIN);
    while (rand3.length() < 8)
    {
        rand3 = "0" + rand3;
    }
    rand1before = rand1;
    rand2before = rand2;
    return rand3;
}

void Alcodisplay::clear()
{
    pixels.clear();
}
