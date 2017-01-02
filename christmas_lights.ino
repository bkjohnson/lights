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
int time[NUM_LEDS];
int dim[NUM_LEDS];

void setup() { 
	Serial.begin(57600);
	Serial.println("resetting");
	LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
	LEDS.setBrightness(84);

        for (int i = 0; i < NUM_LEDS; i++){
              leds[i] = Bulb();
              brightness[i] = 5;
              time[i] = NUM_LEDS;
              dim[i] = 0;
        }

        FastLED.show();
}

int glow;
int brightness_min = 80;
int brightness_max = 230;
int changeRate;

void loop()
{
     for (int j = 0; j < NUM_LEDS; j++){
       changeRate = random(7);
       if (time[j] <= 0){  // This bulb has run out of time, so reset it and choose a new bulb
           dim[j] = (dim[j] + 1) % 2;
           time[j] = random(50, 200);
       }

       glow = brightness[j];

       if (glow < brightness_min) {
         glow = glow + changeRate;  // Brightness must increase
       }
       else if (glow <= brightness_max) {
         if (dim[j] == 0){
           glow = glow + changeRate;
         }
         else {
           glow = glow - changeRate;
         }

       }
       else if (glow > brightness_max) {
         glow = glow - changeRate;  // Brightness must decrease
       }

       leds[j].setVal(glow);
       brightness[j] = glow;
       time[j]--;
     }
   delay(random(15,30));
   FastLED.show();  // Show lights after all have been updated for this round
}
