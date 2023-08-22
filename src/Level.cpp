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

void fillStrip(CRGB* strip, CRGB color);


int LevelManager::randomColor() {
unsigned int sum = weightOne + weightTwo + weightThree;
    long rand = random(sum);
    if (rand < weightOne && previousColor != COLOR_PLAYER_1)
        return COLOR_PLAYER_1;
    if (rand < weightOne + weightTwo && rand > weightOne && previousColor != COLOR_PLAYER_2)
        return COLOR_PLAYER_2;
    return COLOR_PLAYER_3;
}

// int LevelManager::randomColor2() {
// unsigned int sum = weightOne + weightTwo + weightThree;
//     long rand = random(sum);
//     if (rand < weightOne && previousColor2 != COLOR_PLAYER_1)
//         return COLOR_PLAYER_1;
//     if (rand < weightOne + weightTwo && rand > weightOne && previousColo2 != COLOR_PLAYER_2)
//         return COLOR_PLAYER_2;
//     return COLOR_PLAYER_3;
// }


void LevelManager::randomCatch() {
    randomSeed(analogRead(4) + 1);
    float rand_f = random(100);
    rand_f /= 100;
    int defWeight = 25;
    int randMax = int(defWeight * rand_f);
    int rand = random(randMax);
    if (rand < 4)
        rand = 6;
    if (rand >= 15)
        rand = 14;
    catchArea.clear();
    int randStart = random(30);
    if (randStart < 10) {
        randStart = 10;
    }
    for (int i = randStart; i < rand + randStart; i++)
        catchArea.push_back(i);
}

void LevelManager::clear(CRGB* ledStrip) {
    fillStrip(ledStrip, COLOR_EMPTY);
}

void fillPByP(CRGB* ledStrip, CRGB color) {
    for (int i = 0; i < NUM_LEDS; i++){
        ledStrip[i] = color;
        FastLED.show();
        delay(6);
    }
}

void LevelManager::gameOver(CRGB* ledStrip) {
    Serial.write("Game Over!\n");
    fillPByP(ledStrip, CRGB::Red);
    delay(DELAY_SHORT);
    level = 0;
    delayTime = 125;
    generateNextLevel();
}

LevelManager::LevelManager() : level(0) {
    randomSeed(analogRead(4) + 1);
}

int LevelManager::moveColor(CRGB* ledStrip) {
    if (level < 5)
        colorPosition--;
    return 0;
}

void fillStrip(CRGB* strip, CRGB color) {
    for (int idx = 0; idx < NUM_LEDS; idx++)
        strip[idx] = color;
}

void LevelManager::playAnimation(CRGB* ledStrip) {
    // Serial.write(std::to_string(colorPosition).c_str());
    CRGB localCatchColor = COLOR_CATCH;
    clear(ledStrip);
    bool maybeCatched = false;
    bool maybeCatched2 = false;
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
        if ( colorPosition2 == idx)
            maybeCatched2 = true;
    }
    if (maybeCatched) {
        Serial.write("maybe?");
        if (int(playerOnePressed) + int(playerTwoPressed) + int(playerThreePressed) > 1) {
            gameOver(ledStrip); // TODO make ledStrip member
            return;
        } else if (int(playerOnePressed) + int(playerTwoPressed) + int(playerThreePressed) == 1) {
            if (playerOnePressed && currentColor != COLOR_PLAYER_1) {
                gameOver(ledStrip); // TODO make ledStrip member
                return;
            }
            if (playerTwoPressed && currentColor != COLOR_PLAYER_2) {
                gameOver(ledStrip); // TODO make ledStrip member
                return;
            }
            if (playerThreePressed && currentColor != COLOR_PLAYER_3) {
                gameOver(ledStrip); // TODO make ledStrip member
                return;
            }
            fillStrip(ledStrip, COLOR_CATCH);
            FastLED.show();
            delay(DELAY_SHORT);
            fillStrip(ledStrip, COLOR_EMPTY);
            FastLED.show();
            delay(DELAY_SHORT);
            fillStrip(ledStrip, COLOR_CATCH);
            FastLED.show();
            delay(DELAY_SHORT);
            clear(ledStrip); // todo change code in clear to fillstrip
            level++;
            delayTime -= 2;
            generateNextLevel();
        }
    }
    if (colorPosition == 0) {
        Serial.write(std::to_string(colorPosition).c_str());
        Serial.write("Game Over!\n");
        gameOver(ledStrip);
        return;
    }
    ledStrip[colorPosition] = currentColor;
    colorPosition--;
    playerOnePressed = false;
    playerTwoPressed = false;
    playerThreePressed = false;
}

void LevelManager::randomDelay() {
    switch (random(4)) {
        default:
            delayTime = 125;
    }
}

unsigned long LevelManager::speed() { return delayTime; }

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
    if (level < 1) {
        switch(level) {
            case 0:
                // delayTime = 50;
                previousColor = COLOR_EMPTY;
                weightOne = 100;
                weightTwo = 100;
                weightThree = 100;
                currentColor = randomColor();
                colorPosition = NUM_LEDS - 1;
                points = 1;
                catchArea.clear();
                catchArea = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
                break;
            case 1:
                // delayTime = 50;
                previousColor = currentColor;
                weightOne = 100;
                weightTwo = 100;
                weightThree = 100;
                currentColor = randomColor();
                colorPosition = NUM_LEDS - 1;
                points = 1;
                break;
            case 2:
                // delayTime = 50;
                previousColor = currentColor;
                weightOne = 100;
                weightTwo = 100;
                weightThree = 100;
                currentColor = randomColor();
                colorPosition = NUM_LEDS - 1;
                points = 1;
                break;

        }
    } else {
        previousColor = currentColor;
        weightOne = 100;
        weightTwo = 100;
        weightThree = 100;
        currentColor = randomColor();
        colorPosition = NUM_LEDS - 1;
        points = 1;
        // delayTime = 50;
        randomCatch();
    }
}