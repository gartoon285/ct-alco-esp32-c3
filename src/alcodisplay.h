#ifndef alcodisplay
#define alcodisplay
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Alcohol.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3c ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define NUMPIXELS 8 // Popular NeoPixel ring size
#define PIN        7 // On Trinket or Gemma, suggest changing this to 1
#define OLED_RESET -1
#define Time_WormUp 20


const unsigned char FreeWill_Logo [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x07, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x7f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x03, 0xe1, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x03, 0xcf, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x07, 0x9f, 0xcf, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x07, 0x8f, 0x17, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x07, 0x8f, 0x3f, 0xff, 0xe0, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x66, 0x60, 0x78, 0x00, 0x00, 
	0x00, 0x0f, 0x8f, 0x3f, 0xfb, 0xf0, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x66, 0x60, 0x70, 0x00, 0x00, 
	0x00, 0x0f, 0x8f, 0x3e, 0x60, 0xf0, 0x18, 0x00, 0x00, 0x00, 0x00, 0x06, 0x60, 0xe0, 0x00, 0x00, 
	0x00, 0x0f, 0x8f, 0x3f, 0x0f, 0xf0, 0x3c, 0x91, 0xc1, 0xc6, 0x63, 0x66, 0x60, 0xf6, 0x30, 0x00, 
	0x00, 0x0f, 0x9f, 0x3f, 0x8f, 0xf0, 0x3c, 0xf3, 0xe3, 0xe6, 0x66, 0x66, 0x60, 0xf7, 0x60, 0x00, 
	0x00, 0x0f, 0x8f, 0x3f, 0x8f, 0xf0, 0x18, 0xe6, 0x36, 0x36, 0x76, 0x66, 0x60, 0xe3, 0xe0, 0x00, 
	0x00, 0x0f, 0x00, 0x1f, 0x8f, 0xf0, 0x18, 0xc7, 0xf7, 0xf6, 0x76, 0x66, 0x60, 0xe1, 0xc0, 0x00, 
	0x00, 0x0f, 0x8f, 0x3f, 0x8f, 0xf0, 0x18, 0xc7, 0xe7, 0xf3, 0xde, 0x66, 0x60, 0xe1, 0xc0, 0x00, 
	0x00, 0x0f, 0x9f, 0x3f, 0x8f, 0xf0, 0x18, 0xc6, 0x07, 0x03, 0x9c, 0x66, 0x60, 0xe3, 0xe0, 0x00, 
	0x00, 0x07, 0x8f, 0x3f, 0x07, 0xe0, 0x18, 0xc3, 0xe3, 0xe3, 0x9c, 0x66, 0x60, 0xe6, 0x70, 0x00, 
	0x00, 0x07, 0x8e, 0x10, 0x31, 0xe0, 0x18, 0xc1, 0xe1, 0xe1, 0x88, 0x66, 0x20, 0x46, 0x30, 0x00, 
	0x00, 0x07, 0x06, 0x1c, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x03, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x03, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x7f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x03, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


    class Alcodisplay{
        public:
        void init();
        void drawstyles(String co2,String Alcohol);
        String randLED();
        void OLEDclear();
        void DisplayWormUp();
		void sensorDisplay();
        private:
        byte rand1before;
        byte rand2before;
    };
	extern Alcohol sensor;
#endif