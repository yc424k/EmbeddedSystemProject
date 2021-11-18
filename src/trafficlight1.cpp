#include <Adafruit_NeoPixel.h>
#define CAR_PIN1 2
#define CAR_PIN2 5

Adafruit_NeoPixel pixels1(4, CAR_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(4, CAR_PIN2, NEO_GRB + NEO_KHZ800);

void setup(){
    pixels1.begin(); //시작
    pixels2.begin();
}

void loop(){
    pixels1.setPixelColor(0,0,255,0); //초록
    pixels1.setPixelColor(1,0,0,255); //파랑
    pixels1.setPixelColor(2,255,215,0); //주황
    pixels1.setPixelColor(3,255,0,0); //빨강
}