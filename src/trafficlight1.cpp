#include <Adafruit_NeoPixel.h> //네오픽셀 라이브러리
#define CAR_PIN1 2
#define CAR_PIN2 5
#define PEO_PIN1 3
#define PEO_PIN2 4
#define PEO_PIN3 6
#define PEO_PIN4 7
unsigned long l1,l2;   //millis 함수
unsigned long Switch;
unsigned long interval= 1024;
int Time;

Adafruit_NeoPixel pixels1(4, CAR_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(4, CAR_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3(2, PEO_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels4(2, PEO_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels5(2, PEO_PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels6(2, PEO_PIN4, NEO_GRB + NEO_KHZ800);

void setup(){
  Time = 0;
  Switch = 1;
  l1 = 0;
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
  pixels3.show(); // show() = LED 켜기
  pixels4.show();
  pixels5.show();
  pixels6.show();
}

void loop() {
  l2=millis();
  
  switch(Switch){
  case 1: //1번 차량 신호등
    if(l2-l1 >= interval){  // millis함수 한번 도는데 1초 걸림
    l1=l2;
    Time++;
    pixels1.clear(); // clear() = LED 끄기
    if(Time<= 10){
      pixels1.setPixelColor(0,0,255,0); //초록불 
      pixels1.setPixelColor(1,0,0,255); //파란불
      pixels1.show();
      }else if(Time>10 && Time <= 15){
        pixels1.clear();
        pixels1.setPixelColor(2,255,215,0); // 주황불
        pixels1.show();
      }else{
        pixels1.clear();
        pixels1.setPixelColor(3,255,0,0); //빨간불
        pixels1.show();
        Time=0; //초기화
        Switch=2;
        l1=0;
        break;
      }
    }
    case 2: //2번 차량 신호등
    if(l2-l1 >= interval){
    l1=l2;
    Time++;
    pixels2.clear();
    if(Time<= 10){
      pixels2.setPixelColor(0,0,255,0);
      pixels2.setPixelColor(1,0,0,255);
      pixels2.show();
      }else if(Time>10 && Time <= 15){
        pixels2.clear();
        pixels2.setPixelColor(2,255,215,0);
        pixels2.show();
      }else{
        pixels2.clear();
        pixels2.setPixelColor(3,255,0,0);
        pixels2.show();
        Time=0;
        l1=0;
        Switch=3;
        break;
      }
    }
    case 3: //횡단보도 신호등 (전체)
    if(l2-l1 >= interval){
    l1=l2;
    Time++;
    pixels3.clear();
    pixels4.clear();
    pixels5.clear();
    pixels6.clear();
    if(Time<= 3){
      pixels3.setPixelColor(0,0,255,0);
      pixels4.setPixelColor(0,0,255,0);
      pixels5.setPixelColor(0,0,255,0);
      pixels6.setPixelColor(0,0,255,0);
    pixels3.show();
    pixels4.show();
    pixels5.show();
    pixels6.show();
    }else if(Time>3 && Time <=10){
      theaterChase(400); // 깜빡이는 함수 
    }else{
      pixels3.clear();
      pixels4.clear();
      pixels5.clear();
      pixels6.clear();
      pixels3.setPixelColor(1,255,0,0);
      pixels4.setPixelColor(1,255,0,0);
      pixels5.setPixelColor(1,255,0,0);
      pixels6.setPixelColor(1,255,0,0);
      pixels3.show();
      pixels4.show();
      pixels5.show();
      pixels6.show();
      Time=0;
      l1=0;
      Switch=1;
      break;
      }
    }
  }
}

void theaterChase(int wait) {
      for (int b=0; b < 3; b++) {
        pixels3.clear();
        pixels4.clear();
        pixels5.clear();
        pixels6.clear();
        for (int c=b; c < 1; c=c+3) {
          pixels3.setPixelColor(c, 0,255,0);
          pixels4.setPixelColor(c, 0,255,0); 
          pixels5.setPixelColor(c, 0,255,0); 
          pixels6.setPixelColor(c, 0,255,0); 
      }
        pixels3.show();
        pixels4.show();
        pixels5.show();
        pixels6.show();
        delay(wait);
  } 
}