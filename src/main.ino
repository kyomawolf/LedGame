#include <Arduino.h>


#include <FastLED.h>
#include "Level.hh"
#include "defs.h"
#include "errno.h"
#include "newLevel.h"

#define HARDWARE_INPUT

CRGB leds[NUM_LEDS];
int playerPosition = 0;
int currentLevel = 0;

bool playerOneMoved = false;
bool playerTwoMoved = false;
bool playerThreeMoved = false;
unsigned long lastTime = millis();

newLevel levelHandler = newLevel();


enum direction {first, second, third};

void setup()
{
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  Serial.begin(115200);
  delay(1000);
  pinMode(PIN_PLAYER_1, INPUT_PULLUP);
  pinMode(PIN_PLAYER_2, INPUT_PULLUP);
  pinMode(PIN_PLAYER_3, INPUT_PULLUP);

  // Serial.print("hello player one!\n");
  // leds[playerPosition] = COLOR_PLAYER_1;
  // leds[12] = CRGB::Blue;
  // leds[13] = CRGB::Yellow;
  // leds[14] = CRGB::Magenta;
  // leds[15] = CRGB::Orange;
  // leds[16] = CRGB::Yellow;
  // leds[17] = CRGB::Cyan;
  // leds[18] = CRGB::Magenta;
  // leds[19] = CRGB::White;
  // leds[NUM_LEDS - 1] = CRGB::Pink;

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


// bool    action(int position, instruction action, int target, int playerColor) {
//   if (playerColor != 0 && levelHandler.getCurrentPlayer() != 0 && playerColor != levelHandler.getCurrentPlayer()) {
//       playerPosition = target;
//       leds[position] = COLOR_EMPTY; // todo consider removal
//       leds[target] = COLOR_PLAYER_1; // todo fix color
//     return false;
//   }
//   playerPosition = target;
//   switch(action) {
//       case JUMP:
//         leds[position] = COLOR_EMPTY; // todo consider removal
//         leds[target] = COLOR_PLAYER_1; // todo fix color
//         break;
//       case FIN:
//         leds[position] = COLOR_EMPTY; // todo consider removal
//         leds[target] = COLOR_PLAYER_1; // todo fix color
//         break;
//       case RESET:
//         break;
//   }
//   FastLED.show();
//   return true;
// }

// void  mapMap() {
//   Level currentLevel = levelHandler.getLevel();
//   CRGB color;
//   for (auto &idx : currentLevel) {
//     switch(std::get<1>(idx)) {
//       case JUMP:
//         color = COLOR_JUMP;
//         break;
//       case FIN:
//         color = COLOR_FIN;
//         break;
//       case RESET:
//         color = COLOR_RESET;
//         break;
//     }
//     leds[std::get<0>(idx)] = color;
//   }
//   leds[playerPosition] = COLOR_PLAYER_0;
// }

void serialFlush() {
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
}

void loop() {
  if (digitalRead(PIN_PLAYER_1) == LOW)
     {levelHandler.player[0] = true; }
  else if (digitalRead(PIN_PLAYER_2) == LOW)
      {levelHandler.player[1] = true; }
   else if (digitalRead(PIN_PLAYER_3) == LOW)
     { levelHandler.player[2] = true; }
  levelHandler.cycle(leds);
}
