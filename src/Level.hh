#pragma once
#include <FastLED.h>
#include <vector>
#include "defs.h"

enum instruction { JUMP, FIN, RESET };

bool    action(int position, instruction action, int target, int playerColor);
void    resetLeds();

/* tuple for one action:
    first int: position of instruction
    second instruction: what is going to happen
    third int: where to 
    fourth int: who can trigger this instruction
*/
typedef std::vector< std::tuple<int, instruction, int, int> >  Level;
std::vector<Level> cursedLevelCreator();

class LevelManager {
public:
    LevelManager();
    void    generateNextLevel();
    void    triggered(int playerColor);
    void    playAnimation(CRGB* ledStrip);

    int randomColor();
    
    CRGB     randomColor(bool first, bool second, bool third);
    void    setPressed(int player);
    void    gameOver();
    void    clear(CRGB* ledStrip);
private:
    long score;
    int points;
    long level;
    CRGB nextColor;
    CRGB currentColor;
    CRGB previousColor;
    int colorPosition;
    float difficulty;
    float difficultyFactor;
    std::vector<int> catchArea = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    unsigned int weightOne;
    unsigned int weightTwo;
    unsigned int weightThree;

    bool playerOnePressed;
    bool playerTwoPressed;
    bool playerThreePressed;

};