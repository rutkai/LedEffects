#include <EEPROM.h>
#include <FastLED.h>
#include "color.h"
#include "easing.h"
#include "ripple.h"
#include "juggle.h"
#include "lightning.h"
#include "rainbow.h"

#define PIN 3
#define MAX_LEDS 120

uint8_t led_number = 0;
CRGB leds[MAX_LEDS];

char inputString[100];           // a string to hold incoming data
int inputPointer = 0;
boolean stringComplete = false;  // whether the string is complete

uint8_t mode = 0;
uint8_t speed = 100;
uint8_t params[3];

uint8_t readInt(uint8_t);

void setup() {
  Serial.begin(9600);
  loadDefaults();
  FastLED.addLeds<WS2812B, PIN, GRB>(leds, led_number);
  FastLED.setBrightness(255);

  Serial.println("LedEffects has been started!");
  Serial.println("For the available commands please enter help.");
}

void loadDefaults() {
  if (sizeof(params) + 2 < EEPROM.length()) {
    led_number = EEPROM.read(0);
    mode = EEPROM.read(1);
    for (uint8_t i = 0; i < sizeof(params) / sizeof(uint8_t); ++i) {
      params[i] = EEPROM.read(i + 2);
    }
  } else {
    led_number = 8;
    mode = 0;
    for (uint8_t i = 0; i < sizeof(params) / sizeof(uint8_t); ++i) {
      params[i] = 0;
    }
  }
}

void loop() {
  EVERY_N_MILLISECONDS(speed) {
    serialEvent();
    if (stringComplete) {
      changeMode();
      stringComplete = false;
      inputPointer = 0;
    }
  
    switch (mode) {
      case 0:
        Color::colorRGB(leds, led_number, params[0], params[1], params[2]);
        break;
      case 1:
        Ripple::ripple(leds, led_number);
        break;
      case 2:
        Easing::ease(leds, led_number);
        break;
      case 3:
        Lightning::lightning(leds, led_number);
        break;
      case 4:
        Rainbow::rainbow(leds, led_number);
        break;
      case 5:
        Juggle::juggle(leds, led_number);
        break;
      default:
        Color::colorRGB(leds, led_number, 0, 0, 0);
        break;
    }
  }

  FastLED.show();
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    inputString[inputPointer] = (char)Serial.read();
    Serial.write(inputString[inputPointer]);
    if (inputString[inputPointer] == '\n' || inputString[inputPointer] == '.') {
      inputString[inputPointer] = '\0';
      stringComplete = true;
    }
    inputPointer++;
  }
}

void changeMode() {
  char* command = strtok(inputString, " ");
  speed = 100;
  if (!strcmp(command, "leds")) {
    led_number = readInt(8);

    if (led_number > MAX_LEDS) {
      Serial.print("Maximum number of leds: ");
      Serial.println(MAX_LEDS);
      return;
    }
    
    Serial.println("New led number is set. Please restart Arduino.");
  } else if (!strcmp(command, "color")) {
    params[0] = readInt(0);
    params[1] = readInt(0);
    params[2] = readInt(0);
    Serial.print("Setting color to (RGB): ");
    Serial.print(params[0]);
    Serial.print(" ");
    Serial.print(params[1]);
    Serial.print(" ");
    Serial.println(params[2]);
    mode = 0;
  } else if (!strcmp(command, "ripple")) {
    speed = readInt(100);
    Serial.println("Enabling RIPPLE effect");
    mode = 1;
  } else if (!strcmp(command, "ease")) {
    speed = readInt(100);
    Serial.println("Enabling EASING effect");
    mode = 2;
  } else if (!strcmp(command, "lightning")) {
    params[0] = readInt(50);
    params[1] = readInt(8);
    Lightning::set(params[0], params[1]);
    Serial.println("Enabling LIGHTNING effect");
    mode = 3;
  } else if (!strcmp(command, "rainbow")) {
    params[0] = readInt(10);
    params[1] = readInt(0);
    speed = readInt(100);
    Rainbow::set(params[1], params[0]);
    Serial.println("Enabling RAINBOW effect");
    mode = 4;
  } else if (!strcmp(command, "juggle")) {
    speed = readInt(100);
    Serial.println("Enabling JUGGLE effect");
    mode = 5;
  } else {
    Serial.println("Commands:");
    Serial.println("  leds <number, default: 8>   (sets the number of leds)");
    Serial.println("  color <red> <green> <blue>");
    Serial.println("  ease <speed, default: 100>");
    Serial.println("  ripple <speed, default: 100>");
    Serial.println("  lightning <frequency, default: 50> <flashes, default: 8>");
    Serial.println("  rainbow <deltahue, default: 10> <starthue, default: 0> <speed, default: 100>");
    Serial.println("  juggle <speed, default: 100>");
  }
  writeDefaults();
}

uint8_t readInt(uint8_t def) {
  char* str = strtok(0, " ");
  if (str != 0) {
    return atoi(str);
  }
  return def;
}

void writeDefaults() {
  if (sizeof(params) + 2 < EEPROM.length()) {
    EEPROM.write(0, led_number);
    EEPROM.write(1, mode);
    for (uint8_t i = 0; i < sizeof(params) / sizeof(uint8_t); ++i) {
      EEPROM.write(i + 2, params[i]);
    }
  }
}

