#include "Level.hh"
#include <iostream>
#include <tuple>
//#include "Arduino.h"
extern long random(long);
extern uint16_t analogRead(uint8_t);
extern void randomSeed(unsigned long);

extern int playerPosition;
extern bool playerOneMoved;
extern bool playerTwoMoved;
extern bool playerThreeMoved;


int LevelManager::randomColor() {
    unsigned int sum = weightOne + weightTwo + weightThree;
    long rand = random(sum);
    if (rand < weightOne)
        return COLOR_PLAYER_1;
    if (rand < weightTwo)
        return COLOR_PLAYER_2;
    return COLOR_PLAYER_3;
}

void LevelManager::clear(CRGB* ledStrip) {
    for (int i = 0; i < NUM_LEDS; i++)
        ledStrip[i] = COLOR_EMPTY;
}

void LevelManager::gameOver() { level = 0; }

LevelManager::LevelManager() : level(0) {
    randomSeed(analogRead(4) + 1);
}

void LevelManager::playAnimation(CRGB* ledStrip) {
    CRGB localCatchColor = COLOR_CATCH;
    clear(ledStrip);
    bool maybeCatched = false;
    if (playerOnePressed)
        localCatchColor = COLOR_PLAYER_1;
    else if (playerTwoPressed)
        localCatchColor = COLOR_PLAYER_2;
    else if(playerThreePressed)
        localCatchColor = COLOR_PLAYER_3;
    for (auto& idx : catchArea) {
        ledStrip[idx] = localCatchColor;
        if (colorPosition == idx)
            maybeCatched = true;
    }
    if (maybeCatched) {
        Serial.write("maybe?");
        if (int(playerOnePressed) + int(playerTwoPressed) + int(playerThreePressed) > 1) {
            Serial.write("Game Over!\n");
            gameOver();
            return;
        } else if (int(playerOnePressed) + int(playerTwoPressed) + int(playerThreePressed) == 1) {
            level++;
            generateNextLevel();
        }
    }
    if (colorPosition == 0) {
        Serial.write("Game Over!\n");
        gameOver();
        return;
    }
    ledStrip[colorPosition] = currentColor;
    colorPosition--;
    playerOnePressed = false;
    playerTwoPressed = false;
    playerThreePressed = false;
}

void    LevelManager::setPressed(int player) {
    switch (player) {
        case 1:
            playerOnePressed = true;
            break;
        case 2:
            playerTwoPressed = true;
            break;
        case 3:
            playerThreePressed = true;
            break;
        default:
            break;
    }
}

void LevelManager::generateNextLevel() {
    if (level < 3) {
        switch(level) {
            case 0:
                previousColor = COLOR_EMPTY;
                weightOne = 100;
                weightTwo = 100;
                weightThree = 100;
                currentColor = randomColor();
                colorPosition = NUM_LEDS - 1;
                points = 3;
                break;
            case 1:
                previousColor = COLOR_EMPTY;
                weightOne = 100;
                weightTwo = 100;
                weightThree = 100;
                currentColor = randomColor();
                colorPosition = NUM_LEDS - 1;
                points = 3;
                break;
            case 2:
                previousColor = COLOR_EMPTY;
                weightOne = 100;
                weightTwo = 100;
                weightThree = 100;
                currentColor = randomColor();
                colorPosition = NUM_LEDS - 1;
                points = 3;
                break;

        }
    } else {
        // todo generate procedural
    }
}