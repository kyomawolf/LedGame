#pragma once
#include <FastLED.h>
#include "defs.h"


class Led {
public:
    Led();
    ~Led();
    CRGB* getLedBar();
private:
    CRGB ledBar[NUM_LEDS];
    int playerPosition;

};
