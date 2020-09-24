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
  const static uint8_t hue = 35;
  const static uint8_t saturation = 200;

  public:

    Bulb()
    {
      setHSV(hue, saturation, 50);
    }

    void setVal(int val)
    {
      setHSV(hue, saturation, val);
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
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = Bulb();
    time[i] = NUM_LEDS;
    dim[i] = false;
  }
}


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
  int glow;
  int changeRate;

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
