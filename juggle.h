#ifndef JUGGLE_H
#define JUGGLE_H

class Juggle {
  public:
    static void juggle(CRGB leds[], uint8_t led_number) {
      fadeToBlackBy(leds, led_number, 20);
      byte dothue = 0;
      for (int i = 0; i < 8; i++) {
        leds[beatsin16(i + 7, 0, led_number)] |= CHSV(dothue, 200, 255);
        dothue += 32;
      }
    }
};

#endif
