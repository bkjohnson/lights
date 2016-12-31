#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 50

// Must be < NUM_LEDS
#define NUM_TO_CHANGE 7

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
int rate[NUM_TO_CHANGE];
int time[NUM_LEDS];

void setup() { 
	Serial.begin(57600);
	Serial.println("resetting");
	LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
	LEDS.setBrightness(84);

        for (int i = 0; i < NUM_LEDS; i++){
              leds[i] = Bulb();
              brightness[i] = 5;
              time[i] = NUM_LEDS;
        }

        for (int j = 0; j < NUM_TO_CHANGE; j++){
             rate[j] = 1 + (j % 4); // We never want our rate to be faster than 3
        }
        FastLED.show();
}

int randLight;
int glow;
int changers[NUM_TO_CHANGE];
int dim = 0; // treat this as a boolean indicating whether or not to dim the light
int brightness_min = 60;
int brightness_max = 250;

void loop()
{
   // Pick which LEDs will be updated
   for(int i = 0; i < NUM_TO_CHANGE; i++ )
   {
     changers[i] = random(NUM_LEDS);
   }

   dim = random(2);
   for (int k = 0; k < 150; k++){
     // Update each of the chosen LEDs
     for (int j = 0; j < NUM_TO_CHANGE; j++){
       if (time[changers[j]] <= 0){  // This bulb has run out of time, so reset it and choose a new bulb
           time[changers[j]] = random(200);
           changers[j] = random(NUM_LEDS);
       }

       glow = brightness[changers[j]];

       if (glow < brightness_min) {
         glow = glow + rate[j];  // Brightness must increase
       }
       else if (glow <= brightness_max) {
         if (dim == 0){
           glow = glow + rate[j];
         }
         else {
           glow = glow - rate[j];
         }

       }
       else if (glow > brightness_max) {
         glow = glow - rate[j];  // Brightness must decrease
       }

       leds[changers[j]].setVal(glow);
       brightness[changers[j]] = glow;
       time[changers[j]]--;
     }
   delay(15);
   FastLED.show();  // Show lights after all have been updated for this round
   }
}
