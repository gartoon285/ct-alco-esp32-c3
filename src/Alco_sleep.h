#ifndef alco_sleep
#define alco_sleep
#define INTERRUPT_PIN 3
#include "Arduino.h"
    class EspSleep {
        public:
        void init();
        void ButtonSleep(int t);
        private:
        unsigned long pressB=0;
    };
#endif