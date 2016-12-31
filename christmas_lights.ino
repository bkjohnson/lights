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
     setHSV(35,200,50);
   }

   void setVal(int val)
   {
     setHSV(35,200,val);
   }

   void activate()
   {
     for (int i = 50; i < 100; i++){
       setHSV(35,200,i + 100);
       delay(5);
       FastLED.show();
     }
     for (int i = 50; i > 0; i--){
       setHSV(35,200,i + 100);
       delay(5);
       FastLED.show();
     }
   }

};

// Define the array of leds
Bulb leds[NUM_LEDS];
int brightness[NUM_LEDS];

void setup() { 
	Serial.begin(57600);
	Serial.println("resetting");
	LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
	LEDS.setBrightness(84);

        for (int i = 0; i < NUM_LEDS; i++){
              leds[i] = Bulb();
              brightness[i] = 5;
        }
        FastLED.show();
}

int randLight;
int glow;
int changers[NUM_LEDS/15];
int dim = 0; // treat this as a boolean indicating whether or not to dim the light

void loop()
{
   // Pick which LEDs will be updated
   for(int i = 0; i < NUM_LEDS/15; i++ )
   {
     changers[i] = random(NUM_LEDS);
   }

   dim = random(2);
   for (int k = 0; k < 50; k++){
     // Update each of the chosen LEDs
     for (int j = 0; j < NUM_LEDS/15; j++){
       glow = brightness[changers[j]];

       if (glow < 60) {
         glow = glow + 1;  // Brightness must increase
       }
       else if (glow <= 150) {
         if (dim == 0){
           glow = glow + 1;
         }
         else {
           glow = glow - 1;
         }

       }
       else if (glow > 150) {
         glow = glow - 1;  // Brightness must decrease
       }

       leds[changers[j]].setVal(glow);
       brightness[changers[j]] = glow;
     }
   delay(5);
   FastLED.show();
   }
}
