#ifndef EASING_H
#define EASING_H

class Easing {
	
public:
	static void ease(CRGB leds[], uint8_t led_number) {
    static uint8_t easeOutVal = 0;
    static uint8_t easeInVal  = 0;
    static uint8_t lerpVal    = 0;
  
    easeOutVal = ease8InOutQuad(easeInVal);
    easeInVal++;
  
    lerpVal = lerp8by8(0, led_number, easeOutVal);
  
    leds[lerpVal] = CRGB::Red;
    fadeToBlackBy(leds, led_number, 16);
	}
};

#endif
