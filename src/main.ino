#include <FastLED.h>
#include <Arduino.h>
#include "Level.hh"
#define NUM_LEDS 22
#define DATA_PIN 17
#define BRIGHTNESS 64

#define COLOR_PLAYER_0    CRGB::Coral;
#define COLOR_PLAYER_1    CRGB::Cyan;
#define COLOR_PLAYER_2    CRGB::Red;
#define COLOR_PLAYER_3    CRGB::Green;
#define COLOR_JUMP        CRGB::White;
#define COLOR_FIN         CRGB::Orange;
#define COLOR_RESET       CRGB::Coral;
#define COLOR_EMPTY       CRGB::Black
// #define COLOR_BLOCKER     CRGB::Red
// #define COLOR_TRIGGER_ONE CRGB::White
// #define COLOR_TRIGGER_TWO CRGB::Magenta
#define DELAY_TIMER       200

CRGB leds[NUM_LEDS];
int playerPosition = 0;
int currentLevel = 0;

bool playerOneMoved = false;
bool playerTwoMoved = false;
bool playerThreeMoved = false;

LevelManager levelHandler = LevelManager();


enum direction {first, second, third};

void setup()
{
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  Serial.begin(115200);
  delay(1000);
  Serial.print("hello player one!\n");
  leds[playerPosition] = COLOR_PLAYER_1;
  // leds[12] = CRGB::Red;
  // leds[13] = CRGB::Green;
  // leds[14] = CRGB::Blue;
  // leds[15] = CRGB::Orange;
  // leds[16] = CRGB::Yellow;
  // leds[17] = CRGB::Cyan;
  // leds[18] = CRGB::Magenta;
  // leds[19] = CRGB::White;
  // leds[20] = CRGB::Pink;

}

void  resetLeds() {
  for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = COLOR_EMPTY;
}

void  move_player(direction direct) {
  leds[playerPosition++] = COLOR_EMPTY;
  correct_position();
  if (direct == first) {
    leds[playerPosition] = COLOR_PLAYER_1;
  } else if (direct == second) {
    leds[playerPosition] = COLOR_PLAYER_2;
  } else if (direct == third) {
    leds[playerPosition] = COLOR_PLAYER_3;
  }
  FastLED.show();
  delay(200);
}

void  correct_position() {
  // correct negative value position
  if (playerPosition < 0)
      playerPosition = NUM_LEDS - 1;
  // correct overflow value position
  playerPosition = playerPosition % NUM_LEDS;
}


bool    action(int position, instruction action, int target, int playerColor) {
  if (playerColor != 0 && levelHandler.getCurrentPlayer() != 0 && playerColor != levelHandler.getCurrentPlayer()) {
      playerPosition = target;
      leds[position] = COLOR_EMPTY; // todo consider removal
      leds[target] = COLOR_PLAYER_1; // todo fix color
    return false;
  }
  playerPosition = target;
  switch(action) {
      case JUMP:
        leds[position] = COLOR_EMPTY; // todo consider removal
        leds[target] = COLOR_PLAYER_1; // todo fix color
        break;
      case FIN:
        leds[position] = COLOR_EMPTY; // todo consider removal
        leds[target] = COLOR_PLAYER_1; // todo fix color
        break;
      case RESET:
        break;
  }
  FastLED.show();
  return true;
}

void  mapMap() {
  Level currentLevel = levelHandler.getLevel();
  CRGB color;
  for (auto &idx : currentLevel) {
    switch(std::get<1>(idx)) {
      case JUMP:
        color = COLOR_JUMP;
        break;
      case FIN:
        color = COLOR_FIN;
        break;
      case RESET:
        color = COLOR_RESET;
        break;
    }
    leds[std::get<0>(idx)] = color;
  }
  leds[playerPosition] = COLOR_PLAYER_0;
}

void loop() {
  mapMap();
  FastLED.show();
  while (Serial.available() > 0) {
    int in = Serial.read();
    // Serial.write(in);
    mapMap();
    FastLED.show();
    switch (in) {
    case ('a'):
      if (playerOneMoved)
        break;
      move_player(first);
      move_player(first);
      move_player(first);
      playerOneMoved = true;
      levelHandler.setPlayer(1);
      break;
    case ('s'):
      if (playerTwoMoved)
        break;
      move_player(second);
      move_player(second);
      move_player(second);
      playerTwoMoved = true;
      levelHandler.setPlayer(2);
      break;
    case ('d'):
      if (playerThreeMoved)
        break;
      move_player(third);
      move_player(third);
      move_player(third);
      playerThreeMoved = true;
      levelHandler.setPlayer(3);
      break;
    }

    yield();
    levelHandler.callToAction();
    yield();
  }
  // todo  player timeout function
}
