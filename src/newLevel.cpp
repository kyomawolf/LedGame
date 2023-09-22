#include <Arduino.h>
#include <FastLED.h>
#include "defs.h"
#include "newLevel.h"

newLevel::newLevel() :
    catched(0), positionCatch(0), sizeCatch(8), cycleDelay(80), ledDelay(700), player(3, false), lastTime(millis()), lastTimeLed(0) {
}

unsigned long newLevel::getCycleDelay() {
    return cycleDelay;
}

void    newLevel::spawnLed() {
    int playerOneAmount = 0;
    int playerTwoAmount = 0;
    int playerThreeAmount = 0;
    CRGB nextColor;
    long maxRand = 0;

    for (auto& idx : colorPosition) {
        if (idx.color == COLOR_PLAYER_1)
            playerOneAmount++;
        if (idx.color == COLOR_PLAYER_2)
            playerTwoAmount++;
        if (idx.color == COLOR_PLAYER_3)
            playerTwoAmount++;
    }
    if ((playerOneAmount + playerTwoAmount + playerThreeAmount) % 3 == 0)
        maxRand = 3;
    
    long num = random(0, 3);
    if (num == 0)
        nextColor = COLOR_PLAYER_1;
    if (num == 1)
        nextColor = COLOR_PLAYER_2;
    if (num == 2)
        nextColor = COLOR_PLAYER_3;
    colorPosition.push_back({nextColor, NUM_LEDS - 1});
    Serial.write("generated new color\n");
}

int newLevel::matchPlayerColor(CRGB color) {
    int retval = 0;
    bool catched = false;
    if (player[0]) {
        if (color == COLOR_PLAYER_1)
            catched = true;
        else
            retval += 2;
    }
    if (player[1]) {
        if (color == COLOR_PLAYER_2 && !catched)
            catched = true;
        else
            retval += 2;
    }
    if (player[2]) {
        if (color == COLOR_PLAYER_3 && !catched)
            catched = true;
        else
            retval += 2;
    }
    if (catched)
        return 1;
    if (retval > 1)
        return -1;
    return retval;
}

void    newLevel::removeColor(size_t pos) {
    for (auto idx = colorPosition.begin(); idx != colorPosition.end(); idx++)
    {
        if (idx->position == pos){
            colorPosition.erase(idx);
            break;
        }
    }

}

int newLevel::checkCatched(CRGB* leds) {
    size_t toBeRemoved = -1;
    int result;
    for (auto& idx : colorPosition) {
        if (!(idx.position >= positionCatch && idx.position < positionCatch + sizeCatch))
            continue;
        result = matchPlayerColor(idx.color);
        printf("result: %i\n", result);
        if (result == -1)
            return result;
        if (result != 0) {
            toBeRemoved = idx.position;
            break;
        }
        if (idx.position == 0)
            return -1;
    }
    printf("toberemoved: %i\n", toBeRemoved);
    if (result == 1) {
        printf("remove\n");
        removeColor(toBeRemoved);
    }
    return 0;
}

void newLevel::gameOver(CRGB* leds) {
    colorPosition.clear();
    clear(leds);
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = COLOR_RESET;
        FastLED.show();
        delay(10);
    }
}

void    newLevel::clear(CRGB* leds) {
    for (auto i = 0; i < NUM_LEDS; i++)
        leds[i] = COLOR_EMPTY;
}

CRGB newLevel::coloring() {
    if (player[0] && player[1])
        return blend(COLOR_PLAYER_1, COLOR_PLAYER_2, 127);
    if (player[0] && player[2])
        return blend(COLOR_PLAYER_1, COLOR_PLAYER_3, 127);
    if (player[1] && player[3])
        return blend(COLOR_PLAYER_2, COLOR_PLAYER_3, 127);
    if (player[0])
        return COLOR_PLAYER_1;
    if (player[1])
        return COLOR_PLAYER_2;
    if (player[2])
        return COLOR_PLAYER_3;
    return COLOR_CATCH;
}

void    newLevel::render(CRGB* leds) {
    clear(leds);
    CRGB color = coloring();
    for (int idx = positionCatch; idx < sizeCatch; idx++) {
        leds[idx] = color;
    }
    for (auto& idx : colorPosition) {
        leds[idx.position] = idx.color;
    }
    FastLED.show();
}


void    newLevel::updateLeds() {
    for (auto & idx : colorPosition)
        idx.position--;
}

void    newLevel::cycle(CRGB* leds) {
    unsigned long currentTime = millis();
    char buffer[40];
    if (currentTime - lastTime < cycleDelay)
        return;
    // Serial.write("in\n");
    if (currentTime - lastTimeLed > ledDelay) {
        spawnLed();
        lastTimeLed = currentTime;
    }

    if (checkCatched(leds) == -1)
        gameOver(leds);
    
    // reset player push position
    // update last time cycle

    render(leds);
    updateLeds();
    setPlayer({false, false, false});
    lastTime = millis();
}

void newLevel::setPlayer(std::tuple<bool, bool, bool> newSet) {
    player[0] = std::get<0>(newSet);
    player[1] = std::get<1>(newSet);
    player[2] = std::get<2>(newSet);
}