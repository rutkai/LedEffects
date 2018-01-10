#ifndef RAINBOW_H
#define RAINBOW_H

class Rainbow {
private:
  static uint8_t hue;
  static uint8_t delta;
public:
  static void set(uint8_t h, uint8_t d) {
    hue = h;
    delta = d;
  }
  static void rainbow(CRGB leds[], uint8_t led_number) {
    hue++;
    fill_rainbow(leds, led_number, hue, delta);
  }
};

uint8_t Rainbow::hue = 0;
uint8_t Rainbow::delta = 10;

#endif
