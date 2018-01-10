#ifndef RIPPLE_H
#define RIPPLE_H

class Ripple {
  private:
    static uint8_t colour;              // Ripple colour is randomized.
    static int center;                  // Center of the current ripple.
    static int step;                    // -1 is the initializing step.
    static uint8_t myfade;              // Starting brightness.
    static uint8_t bgcol;               // Background colour rotates.
  public:
    static void ripple(CRGB leds[], uint8_t led_number) {
      for (int i = 0; i < led_number; i++) {
        leds[i] = CHSV(bgcol++, 255, 15);  // Rotate background colour.
      }

      switch (step) {
        case -1:                                                         // Initialize ripple variables.
          center = random(led_number);
          colour = random8();
          step = 0;
          break;
        case 0:
          leds[center] = CHSV(colour, 255, 255);                         // Display the first pixel of the ripple.
          step++;
          break;
        case 16:                                                         // At the end of the ripples.
          step = -1;
          break;
        default:                                                         // Middle of the ripples.
          leds[(center + step + led_number) % led_number] += CHSV(colour, 255, myfade / step * 2);   // Simple wrap from Marc Miller
          leds[(center - step + led_number) % led_number] += CHSV(colour, 255, myfade / step * 2);
          step++;                                                        // Next step.
          break;
      }
    }
};

uint8_t Ripple::colour = 0;                // Center of the current ripple.
int Ripple::center = 0;                // Center of the current ripple.
int Ripple::step = -1;                 // -1 is the initializing step.
uint8_t Ripple::myfade = 255;          // Starting brightness.
uint8_t Ripple::bgcol = 0;             // Background colour rotates.

#endif
