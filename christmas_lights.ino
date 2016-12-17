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

        for (int i = 0; i < NUM_LEDS; i++){
              //randLight = random(NUM_LEDS);
              leds[i].setRGB(20,10,10);  // setRGB functions works by setting
              
              //brightness = leds[randLight].getLuma();
        }
}

int plus_min;
int randLight;
int glow = 30;
int brightness = 0;
int fadeAmount = 5;

void loop()
{  
  /*brightness = brightness + fadeAmount;
  
  // reverse the direction of the fading at the ends of the fade:
  if(brightness == 0 || brightness == 255)
  {
    fadeAmount = -fadeAmount ;
  }/**/   
  
  for (int i = 0; i < NUM_LEDS/6; i++){
    randLight = random(NUM_LEDS);
    //leds[randLight].setRGB(200,110,10);  // setRGB functions works by setting
    
    brightness = leds[randLight].getLuma();
    
  
    // reverse the direction of the fading at the ends of the fade:
    if(brightness > 150)
    {
      brightness = brightness - fadeAmount;
    } 
    else {
      brightness = brightness + fadeAmount;
    }
    
    leds[randLight].fadeLightBy();
    FastLED.show();

  }

  delay(30);  // This delay sets speed of the fade. I usually do from 5-75 but you can always go higher.
}
