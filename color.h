#ifndef COLOR_H
#define COLOR_H

class Color {
public:
	static void colorRGB(CRGB leds[], int r, int g, int b) {
  	fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
	}
};

#endif
