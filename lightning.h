#ifndef LIGHTNING_H
#define LIGHTNING_H

class Lightning {
  private:
    static uint8_t frequency;
    static uint8_t flashes;
    static unsigned int dimmer;
    static uint8_t ledstart;
    static uint8_t ledlen;
  public:
    static void set(uint8_t fr, uint8_t fl) {
      frequency = fr;
      flashes = fl;
    }
    static void lightning(CRGB leds[], uint8_t led_number) {
      ledstart = random8(led_number);           // Determine starting location of flash
      ledlen = random8(led_number - ledstart);  // Determine length of flash (not to go beyond NUM_LEDS-1)
      for (int flashCounter = 0; flashCounter < random8(3, flashes); flashCounter++) {
        if (flashCounter == 0) dimmer = 5;      // the brightness of the leader is scaled down by a factor of 5
        else dimmer = random8(1, 3);            // return strokes are brighter than the leader
        fill_solid(leds + ledstart, ledlen, CHSV(255, 0, 255 / dimmer));
        FastLED.show();                         // Show a section of LED's
        delay(random8(4, 10));                  // each flash only lasts 4-10 milliseconds
        fill_solid(leds + ledstart, ledlen, CHSV(255, 0, 0)); // Clear the section of LED's
        FastLED.show();
        if (flashCounter == 0) delay (150);     // longer delay until next flash after the leader
        delay(50 + random8(100));               // shorter delay between strokes
      }
      delay(random8(frequency) * 100);          // delay between strikes
    }
};

uint8_t Lightning::frequency = 50;
uint8_t Lightning::flashes = 8;
unsigned int Lightning::dimmer = 1;
uint8_t Lightning::ledstart = 0;
uint8_t Lightning::ledlen = 0;

#endif
