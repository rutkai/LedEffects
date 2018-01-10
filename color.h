#ifndef COLOR_H
#define COLOR_H

class Color {
public:
	static void colorRGB(CRGB leds[], uint8_t led_number, int r, int g, int b) {
  	fill_solid(leds, led_number, CRGB(r, g, b));
	}
};

#endif
