#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 50

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 11

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
	Serial.begin(57600);
	Serial.println("resetting");
	LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
	LEDS.setBrightness(84);
}

int glow;
int plus_min;

void loop() { 
	for(int i = 0; i < NUM_LEDS; i++) {
                glow = leds[i].r;

                plus_min = random(1);

                if (plus_min == 1){
                  glow = glow + random(3);
                }
                else {
                  glow = glow - random(3);
                }
                leds[i].setRGB( glow + 5, glow, glow);
	}
	FastLED.show(); 
        delay(50);
}
