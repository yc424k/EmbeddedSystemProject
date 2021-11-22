#include <Adafruit_NeoPixel.h> //네오픽셀
#include <Wire.h> //I2C 통신
#define sv 8
#define CAR_PIN1 2 //차량
#define CAR_PIN2 5
#define PEO_PIN1 3 //횡단보도
#define PEO_PIN2 4
#define PEO_PIN3 6
#define PEO_PIN4 7
#define DLE_PIN1 8 //딜레마
#define DLE_PIN2 9
unsigned long l1,l2;
unsigned long interval= 1024; //1초
int Time1,Time3,Time5;
byte c;
Adafruit_NeoPixel pixels1(4, CAR_PIN1, NEO_GRB + NEO_KHZ800);  //네오픽셀 초기화
Adafruit_NeoPixel pixels2(4, CAR_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3(2, PEO_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels4(2, PEO_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels5(2, PEO_PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels6(2, PEO_PIN4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels7(4, DLE_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels8(4, DLE_PIN2, NEO_GRB + NEO_KHZ800);

void setup() {
  Wire.begin(); //I2C 시작
  Time1=0;
  Time3=0;
  Time5=0;
  l1=0;
  pixels1.begin();  //네오픽셀 시작
  pixels2.begin();
  pixels3.begin();
  pixels4.begin();
  pixels5.begin();
  pixels6.begin();
  pixels1.setPixelColor(3,255,0,0);
  pixels2.setPixelColor(3,255,0,0);
  pixels3.setPixelColor(1,255,0,0);
  pixels4.setPixelColor(1,255,0,0);
  pixels5.setPixelColor(1,255,0,0);
  pixels6.setPixelColor(1,255,0,0);
  pixels1.show();  //네오픽셀 LED ON
  pixels2.show();
  pixels3.show();
  pixels4.show();
  pixels5.show();
  pixels6.show();
}
void loop() {
  Wire.beginTransmission(sv); //slave 한테 보내겠다고 하는 거
  Wire.requestFrom(sv,1); // 받겠다고 하는거 1바이트
  l2=millis();
  if(Wire.available()){
      c = Wire.read();
    }
  switch(c){
  case '1': //차향
    if(l2-l1 >= interval){
    l1=l2;
    Time1++;
    pixels1.clear();  //네오픽셀 LED OFF
    if(Time1<=10){  //10초동안 초록색 파란색 LED ON
      pixels1.setPixelColor(0,0,255,0);
      pixels1.setPixelColor(1,0,0,255);
      pixels1.show();
      if(Time1>5){  //5초에서 10초사이에 딜레마 LED ON
        theaterChase(512,2); //깜박이는 함수
      }
      }else if(Time1>10 && Time1 <= 15){ //10초부터 5초동안 주황색 LED ON
        pixels1.clear();
        pixels1.setPixelColor(2,255,215,0);
        pixels1.show();
      }else{ //되돌아 오기 전까지 빨간색 LED ON
        pixels1.clear();
        pixels1.setPixelColor(3,255,0,0);
        pixels1.show();
        Wire.write('2'); //송신
        l1=0;
        Time3=0;
        break;
      }
    }
    case '3': //차량
    if(l2-l1 >= interval){
    l1=l2;
    Time3++;
    pixels2.clear();
    if(Time3<= 3){
      pixels2.setPixelColor(0,0,255,0);
      pixels2.setPixelColor(1,0,0,255);
      pixels2.show();
      if(Time1>5){  //5초에서 10초사이에 딜레마 LED ON
        theaterChase(512,3); //깜박이는 함수
        }
      }else if(Time3>3 && Time3 <= 5){
        pixels2.clear();
        pixels2.setPixelColor(2,255,215,0);
        pixels2.show();
      }else{
        pixels2.clear();
        pixels2.setPixelColor(3,255,0,0);
        pixels2.show();
        Wire.write('4'); //송신
        l1=0;
        Time5=0;
        break;
      }
    }
    case '5': //횡단보도
    if(l2-l1 >= interval){
    l1=l2;
    Time5++;
    pixels3.clear();
    pixels4.clear();
    pixels5.clear();
    pixels6.clear();
    if(Time5<= 3){
      pixels3.setPixelColor(0,0,255,0);
      pixels4.setPixelColor(0,0,255,0);
      pixels5.setPixelColor(0,0,255,0);
      pixels6.setPixelColor(0,0,255,0);
      pixels3.show();
      pixels4.show();
      pixels5.show();
      pixels6.show();
    }else if(Time5>3 && Time5 <=10){
      theaterChase(512,1);
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
      c='1'; //다시 처음으로 
      Time1=0;
      l1=0;
      break;
      }
    }
  }
}

void theaterChase(int wait,int i) { //깜박이는 함수
  switch(i){
    case 1:
      for (int b=0; b < 2; b++) { //b가 증가하면 깜박이는 시간이 길어진다
      	pixels3.clear();
        pixels4.clear();
        pixels5.clear();
        pixels6.clear();
      	for (int c=b; c < 1; c=c+3) {
      	  pixels3.setPixelColor(0, 0,255,0);
          pixels4.setPixelColor(0, 0,255,0); 
          pixels5.setPixelColor(0, 0,255,0); 
          pixels6.setPixelColor(0, 0,255,0); 
      }
        pixels3.show();
        pixels4.show();
        pixels5.show();
        pixels6.show();
        delay(wait);
  	}
    break;
    case 2:
    for (int b=0; b < 2; b++) {
      	pixels7.clear();
      	for (int c=b; c < 1; c=c+3) {
      	  pixels7.setPixelColor(0, 0,0,255);
          pixels7.setPixelColor(1, 0,0,255);
          pixels7.setPixelColor(2, 0,0,255);
          pixels7.setPixelColor(3, 0,0,255);
        }
        pixels7.show();
        delay(wait);
    }
    break;
    case 3:
    for (int b=0; b < 2; b++) {
        pixels8.clear();
      	for (int c=b; c < 1; c=c+3) {
          pixels8.setPixelColor(0, 0,0,255); 
          pixels8.setPixelColor(1, 0,0,255); 
          pixels8.setPixelColor(2, 0,0,255); 
          pixels8.setPixelColor(3, 0,0,255); 
      }
        pixels8.show();
        delay(wait);
    }
    break;
  }
}