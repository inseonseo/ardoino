#include <Adafruit_NeoPixel.h>
#define PIN D5
#define NUMPIXELS 24

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB+NEO_KHZ800);
int delayval =500;//0.5초

void setup() {
  // put your setup code here, to run once:
  pixels.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i,pixels.Color(150,0,0));
  }
  pixels.show();
  delay(delayval);
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    
}
pixels.show();
delay(delayval);
}
