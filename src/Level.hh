#pragma once
#include <FastLED.h>
#include <vector>
#include "defs.h"

class LevelManager {
public:
    LevelManager();
    void    generateNextLevel();
    void    triggered(int playerColor);
    void    playAnimation(CRGB* ledStrip);

    int randomColor();
    
    CRGB    randomColor(bool first, bool second, bool third);
    void     randomCatch();
    void    setPressed(int player);
    void    gameOver(CRGB* ledStrip);
    void    clear(CRGB* ledStrip);
    int     moveColor(CRGB* ledStrip);
    unsigned long speed();
    int     randomColor2();
    void    randomDelay();
    bool    catchedMaybe(CRGB* ledStrip, int color);
private:
    long score;
    int points;
    long level;
    CRGB nextColor;
    CRGB currentColor;
    CRGB previousColor;
    int colorPosition;

    int colorPosition2;
    CRGB currentColor2;
    CRGB previousColor2;

    float difficulty;
    float difficultyFactor;
    std::vector<int> catchArea = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    unsigned int weightOne;
    unsigned int weightTwo;
    unsigned int weightThree;

    bool playerOnePressed;
    bool playerTwoPressed;
    bool playerThreePressed;

    unsigned long delayTime = 125;

};