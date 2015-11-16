#ifndef JUGGLE_H
#define JUGGLE_H

class Juggle {
public:
  static void juggle(CRGB leds[]) {
    fadeToBlackBy(leds, NUM_LEDS, 20);
    byte dothue = 0;
    for(int i = 0; i < 8; i++) {
      leds[beatsin16(i+7,0,NUM_LEDS)] |= CHSV(dothue, 200, 255);
      dothue += 32;
    }
  }
};

#endif
