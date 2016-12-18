#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 50

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 11


class Bulb : public CRGB
{

   public:
   Bulb()
   {
     setHSV(35,200,5);
   }

   void setVal(int val)
   {
     setHSV(35,200,val);
   }

};

// Define the array of leds
Bulb leds[NUM_LEDS];

void setup() { 
	Serial.begin(57600);
	Serial.println("resetting");
	LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
	LEDS.setBrightness(84);

        for (int i = 0; i < NUM_LEDS; i++){
              leds[i] = Bulb();
        }
}

int randLight;

void loop()
{
   for(int i = 0; i < NUM_LEDS/8; i++ )
   {
     randLight = random(NUM_LEDS);
     leds[randLight].setVal(random(150));
   }
   FastLED.show();

  delay(30);  // This delay sets speed of the fade. I usually do from 5-75 but you can always go higher.
}
