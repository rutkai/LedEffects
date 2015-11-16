#define NUM_LEDS 8

#include <FastLED.h>
#include "color.h"
#include "easing.h"
#include "ripple.h"
#include "juggle.h"
#include "lightning.h"
#include "rainbow.h"

#define PIN 3

CRGB leds[NUM_LEDS];

char inputString[100];           // a string to hold incoming data
int inputPointer = 0;
boolean stringComplete = false;  // whether the string is complete

int mode = 0;
int speed = 100;
int params[3];

int readInt(int);

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  for (int i = 0; i <= sizeof(params); ++i) {
    params[i] = 0;
  }
  mode = 0;

  Serial.println("LedEffects has been started!");
  Serial.println("For the available commands please enter help.");
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
        Color::colorRGB(leds, params[0], params[1], params[2]);
        break;
      case 1:
        Ripple::ripple(leds);
        break;
      case 2:
        Easing::ease(leds);
        break;
      case 3:
        Lightning::lightning(leds);
        break;
      case 4:
        Rainbow::rainbow(leds);
        break;
      case 5:
        Juggle::juggle(leds);
        break;
      default:
        Color::colorRGB(leds, 0, 0, 0);
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
  if (!strcmp(command, "color")) {
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
    Serial.println("  color <red> <green> <blue>");
    Serial.println("  ease <speed, default: 100>");
    Serial.println("  ripple <speed, default: 100>");
    Serial.println("  lightning <frequency, default: 50> <flashes, default: 8>");
    Serial.println("  rainbow <deltahue, default: 10> <starthue, default: 0> <speed, default: 100>");
    Serial.println("  juggle <speed, default: 100>");
  }
}

int readInt(int def) {
  char* str = strtok(0, " ");
  int val = def;
  if (str != 0) {
    val = atoi(str);
  }
  return val;
}

