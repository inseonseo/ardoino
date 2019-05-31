#include <Adafruit_NeoPixel.h>
#define PIN D5
#define NUMPIXELS 24

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB+NEO_KHZ800);
int delayval = 500;

void setup() {
  // put your setup code here, to run once:
  pixels.begin();
}

void loop() {
  for(int i=0;i<NUMPIXELS;i+=3){
    pixels.setPixelColor(i,pixels.Color(0,150,0));
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(i+1,pixels.Color(150,0,0));
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(i+2,pixels.Color(0,0,150));
    pixels.show();
    delay(delayval);
  }
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i,pixels.Color(0,0,0));
  }
  pixels.show();
  // put your main code here, to run repeatedly:

}
