#include "Level.hh"
#include <iostream>
#include <tuple>

extern int playerPosition;
extern bool playerOneMoved;
extern bool playerTwoMoved;
extern bool playerThreeMoved;


void gameOver() {}

LevelManager::LevelManager() : level(0) {
}

void LevelManager::playAnimation(CRGB* ledStrip) {
    CRGB localCatchColor = COLOR_CATCH;
    bool maybeCatched = false;
    if (playerOnePressed)
        localCatchColor = COLOR_PLAYER_1;
    else if (playerTwoPressed)
        localCatchColor = COLOR_PLAYER_2;
    else if(playerThreeMoved)
        localCatchColor = COLOR_PLAYER_3;
    for (auto& idx : catchArea) {
        ledStrip[idx] = localCatchColor;
        if (colorPosition == idx)
            maybeCatched = true;
    }
    if (maybeCatched) {
        if (int(playerOnePressed) + int(playerTwoPressed) + int(playerThreePressed) > 1) {
            gameOver();
            return;
        }
        level++;
        generateNextLevel();
    }
    ledStrip[colorPosition] = currentColor;
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
                currentColor = randomColor(1, 1, 1);
                points = 3;
                break;
            case 1:
                points = 3;
                break;
            case 2:
                points = 3;
                break;

        }
    } else {
        // todo generate procedural
    }
}