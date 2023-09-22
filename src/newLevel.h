#pragma once
#include <vector>
#include <tuple>

typedef struct sLed {
    CRGB    color;
    int     position;
}  ledColorPosition;

class newLevel {
public:
    void    clear(CRGB* leds);
    newLevel();
    void    cycle(CRGB* leds);
    void    setPlayer(std::tuple<bool, bool, bool> newSet);
    // bool*   getPlayer();

    unsigned long getCycleDelay();
    void    spawnLed();
    int    checkCatched(CRGB* leds);
    int    matchPlayerColor(CRGB color);
    void    removeColor(size_t idx);
    CRGB coloring();
    void    updateLeds();
    void    gameOver(CRGB* leds);

    void render(CRGB* leds);
    std::vector<bool>   player;
private:

    unsigned long catched;

    int positionCatch;
    int sizeCatch;

    unsigned long cycleDelay;
    unsigned long ledDelay;

    std::vector<ledColorPosition> colorPosition;
    unsigned long lastTime;
    unsigned long lastTimeLed;

};