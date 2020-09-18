#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 50

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 11

// A lower bound representing where the target brightness should be
#define BRIGHTNESS_MIN 80

// An upper bound representing where the target brightness should be
#define BRIGHTNESS_MAX 230


class Bulb : public CRGB
{
  public:
    Bulb()
    {
      setHSV(35, 200, 50);
    }

    void setVal(int val)
    {
      setHSV(35, 200, val);
    }
};

// Define the array of leds
Bulb leds[NUM_LEDS];
int brightness[NUM_LEDS];
int time[NUM_LEDS];
bool dim[NUM_LEDS];

void setup() {
  Serial.begin(57600);
  Serial.println("resetting");
  LEDS.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = Bulb();
    time[i] = NUM_LEDS;
    dim[i] = false;
  }

  FastLED.show();
}

int glow;
int changeRate;

// Decide what the current "glow" value should be
int getGlowValue(int currentGlow, int changeRate, bool isDimming) {
  int newGlow;

  if (currentGlow < BRIGHTNESS_MIN) {
    newGlow = currentGlow + changeRate;
  }
  else if (currentGlow <= BRIGHTNESS_MAX) {
    if (isDimming) {
      newGlow = currentGlow + changeRate;
    }
    else {
      newGlow = currentGlow - changeRate;
    }
  }
  else if (currentGlow > BRIGHTNESS_MAX) {
    newGlow = currentGlow - changeRate;
  }

  return newGlow;
}


void loop()
{
  for (int j = 0; j < NUM_LEDS; j++) {
    changeRate = random(3);
    if (time[j] <= 0) { // This bulb has run out of time, so reset it and choose a new bulb
      dim[j] = !dim[j];
      time[j] = random(50, 200);
    }

    glow = getGlowValue(brightness[j], changeRate, dim[j]);

    leds[j].setVal(glow);
    brightness[j] = glow;
    time[j]--;
  }
  FastLED.show();  // Show lights after all have been updated for this round
}
