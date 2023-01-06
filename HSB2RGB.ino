#include "RGBColor.h"
#include <Adafruit_NeoPixel.h>

#define PIN 7
#define LEDS 60
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800);
RGBColor strip[LEDS];

int nCol = 0;
int saturation = 100;
int brightness = 30;
RGBColor mcol;

unsigned long timer;
int period = 15000;
int animation = 0;
int numAnimation = 3;

void draw() {
  for (int i = 0; i < LEDS; i++) {
    pixels.setPixelColor(i, pixels.Color(mcol.getR(), mcol.getG(), mcol.getB()));
  }
  pixels.show();
}

void (*effect)();

void setup() {
  Serial.begin(9600);
  pixels.begin();
  for (int i = 0; i < LEDS; i++) {
    pixels.setPixelColor(i, pixels.Color(50, 50, 50));
  }
  pixels.show();
  effect = rainbow;
  timer = millis();
}

void loop() {
  if (millis() > timer + period) {
    animation++;
    if (animation >= numAnimation) {
      animation = 0;
    }
    switch (animation) {
      case 0:
        effect = rainbow;
        break;
      case 1:
        effect = tracer;
        break;
      case 2:
        effect = circle;
        break;
      default:
        effect = rainbow;
        break;
    }
    timer = millis();
  }
  effect();
}

void rainbow() {
  int nColl = nCol;
  for (int x = 0; x < LEDS; x++) {
    mcol.hsb2rgb(nColl += 16, saturation, brightness);
    pixels.setPixelColor(x, pixels.Color(mcol.getR(), mcol.getG(), mcol.getB()));
  }
  pixels.show();
  nCol += 1;
  if (nCol > 359)nCol = 0;
}
void circle() {
  mcol.hsb2rgb(nCol, saturation, brightness);
  for (int x = 0; x < LEDS; x++) {
    pixels.setPixelColor(x, pixels.Color(mcol.getR(), mcol.getG(), mcol.getB()));
  }
  pixels.show();
  nCol += 1;
  if (nCol > 359)nCol = 0;
  delay(50);
}
void tracer() {
  for (int x = 0; x < LEDS; x++) { //Копируем из предварительного хранилища
    pixels.setPixelColor(x, pixels.Color(strip[x].getR(), strip[x].getG(), strip[x].getB()));
  }
  pixels.show();
  for (int x = LEDS - 1; x >= 1; x--) {
    strip[x] = strip[x - 1];
  }
  static int eTail;
  if (!eTail) {
    int eHue = random(360);
    eTail = random(5, 20);
    mcol.hsb2rgb(eHue, saturation, brightness);
    strip[0] = mcol;
  } else {
    strip[0] = strip[1];
    strip[0].bri2rgb(map(eTail--,0,20,0,100));
  }
  //pixels.setPixelColor(0,pixels.Color(mcol.getR(), mcol.getG(), mcol.getB()));
  delay(30);

}
