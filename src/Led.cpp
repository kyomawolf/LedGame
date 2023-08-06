#include "Led.h"

Led::Led() {}

CRGB* Led::getLedBar() {
    return ledBar;
}

Led::~Led() {}