#include "rsled.h"

RSLED *strip;

int vals[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
Color colors[10];

void setup() {
  Serial.begin(9600);
  strip = new RSLED(2);
}

void loop() {
//  strip->blink();
  strip->setColors(colors);
//  strip->clear();
  colors[0] = {vals[0], 0, 0};
  colors[1] = {vals[1], 0, 0};
  colors[2] = {vals[2], 0, 0};
  colors[3] = {vals[3], 0, 0};
  colors[4] = {vals[4], 0, 0};
  colors[5] = {vals[5], 0, 0};
  colors[6] = {vals[6], 0, 0};
  colors[7] = {vals[7], 0, 0};
  colors[8] = {vals[8], 0, 0};
  colors[9] = {vals[9], 0, 0};
  delay(50);
  for (int x = 0; x < 10; x++) {
    bool increment = false;
    if (x == 0) {
      increment = true;
    }
    if (x > 0 && vals[x-1] > 5) {
      increment = true;
    }
    if (increment && vals[x] < 30) {
      vals[x] = vals[x] + 1;
    }
  }
}
