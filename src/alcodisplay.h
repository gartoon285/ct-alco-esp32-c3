#ifndef alcodisplay
#define alcodisplay
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3c ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define NUMPIXELS 8 // Popular NeoPixel ring size
#define PIN        7 // On Trinket or Gemma, suggest changing this to 1
#define OLED_RESET -1
    class Alcodisplay{
        public:
        void init();
        void drawstyles(String text);
        String randLED();
        void clear();
        private:
        byte rand1before;
        byte rand2before;
    };
#endif