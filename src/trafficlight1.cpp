#include <Adafruit_NeoPixel.h>
#define CAR_PIN1 2
#define CAR_PIN2 5
#define PEO_PIN1 3
#define PEO_PIN2 4
#define PEO_PIN3 6
#define PEO_PIN4 7

Adafruit_NeoPixel pixels1(4, CAR_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(4, CAR_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3(2, PEO_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels4(2, PEO_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels5(2, PEO_PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels6(2, PEO_PIN4, NEO_GRB + NEO_KHZ800);

void setup(){
  pixels1.begin(); //시작
  pixels2.begin();
  pixels3.begin();
  pixels4.begin();
  pixels5.begin();
  pixels6.begin();
  pixels3.setPixelColor(1,255,0,0); // 횡단보도 신호등 빨강색 ON
  pixels4.setPixelColor(1,255,0,0);
  pixels5.setPixelColor(1,255,0,0);
  pixels6.setPixelColor(1,255,0,0);
  pixels3.show();
  pixels4.show();
  pixels5.show();
  pixels6.show();
}

void loop(){
    pixels1.setPixelColor(0,0,255,0); //초록
    pixels1.setPixelColor(1,0,0,255); //파랑
    pixels1.setPixelColor(2,255,215,0); //주황
    pixels1.setPixelColor(3,255,0,0); //빨강
}