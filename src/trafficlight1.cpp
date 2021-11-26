#include <Adafruit_NeoPixel.h> //네오픽셀
#include <Wire.h> //I2C 통신
#define sv 8

#define CAR_PIN1 2 //차량
#define CAR_PIN2 3
#define CAR_PIN3 4
#define CAR_PIN4 5
#define DLE_PIN1 6 //딜레마
#define DLE_PIN2 7
#define DLE_PIN3 8
#define DLE_PIN4 9
unsigned long l1,l2;
unsigned long interval= 1024; //1초
int Time1,Time2,Time3,Time4;
byte c;
byte a;
byte serial;
Adafruit_NeoPixel pixels1(4, CAR_PIN1, NEO_GRB + NEO_KHZ800);  //네오픽셀 초기화
Adafruit_NeoPixel pixels2(4, CAR_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3(4, CAR_PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels4(4, CAR_PIN4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels5(9, DLE_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels6(9, DLE_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels7(9, DLE_PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels8(9, DLE_PIN4, NEO_GRB + NEO_KHZ800);

void setup() {
  Wire.begin(); //I2C 시작
  Serial.begin(9600);
  Time1=0;
  Time2=0;
  Time3=0;
  Time4=0;
  l1=0;
  pixels1.begin();  //네오픽셀 시작
  pixels2.begin();
  pixels3.begin();
  pixels4.begin();
  pixels5.begin();
  pixels6.begin();
  pixels7.begin();
  pixels8.begin();
  pixels1.clear();
  pixels2.clear();
  pixels3.clear();
  pixels4.clear();
  pixels5.clear();
  pixels6.clear();
  pixels7.clear();
  pixels8.clear();
  pixels1.setPixelColor(3,255,0,0);
  pixels2.setPixelColor(3,255,0,0);
  pixels3.setPixelColor(3,255,0,0);
  pixels4.setPixelColor(3,255,0,0);
  pixels1.show();  //네오픽셀 LED ON
  pixels2.show();
  pixels3.show();
  pixels4.show();
}

void loop() {
  Wire.beginTransmission(sv); //slave 한테 보내겠다고 하는 거
  Wire.requestFrom(sv,1); // 받겠다고 하는거 1바이트
  if(Wire.available()>0){
     c= Wire.read();
  }
  l2=millis();
  switch(c){
    case '1':
    if(l2-l1 >= interval){ //'1'을 받으면 1번 신호등만 켜짐
    pixels2.setPixelColor(3,255,0,0);
    pixels3.setPixelColor(3,255,0,0);
    pixels4.setPixelColor(3,255,0,0);
    pixels2.show();
    pixels3.show();
    pixels4.show();
    pixels1.clear();  // 빨간불을 끄기 위해 1번신호등 끄기
    l1=l2;
    Time1++;
    if(Time1<=10){  //10초동안 초록색 파란색 LED ON
      pixels1.setPixelColor(0,0,255,0);
      pixels1.setPixelColor(1,0,0,255);
      pixels1.show();
      if(Time1>5) //딜레마 존
        callD(512,1);
      }else if(Time1>10 && Time1 <= 13){ //10초부터 5초동안 주황색 LED ON
        pixels1.clear(); 
        pixels1.setPixelColor(2,255,215,0);
        pixels1.show();
      }else{
        pixels1.setPixelColor(3,255,0,0); //빨간불 ON
        pixels1.show();
        Wire.write('1'); // 송신
        l1=0;
        Time2=0;
        break;
      }
    }
    case '2':
    if(l2-l1 >= interval){
      pixels1.setPixelColor(3,255,0,0);
      pixels3.setPixelColor(3,255,0,0);
      pixels4.setPixelColor(3,255,0,0);
      pixels1.show();
      pixels3.show();
      pixels4.show();
      pixels2.clear();
      l1=l2;
      Time2++;
      if(Time2<= 10){
        pixels2.setPixelColor(0,0,255,0);
        pixels2.setPixelColor(1,0,0,255);
        pixels2.show();
        if(Time2>5)
          callD(512,2);
        }else if(Time2>10 && Time2 <= 13){
          pixels2.clear();
          pixels2.setPixelColor(2,255,215,0);
          pixels2.show();
        }else{
          pixels2.setPixelColor(3,255,0,0);
          pixels2.show();
          Wire.write('2');
          l1=0;
          Time3=0;
          break;
        }
      }
    case '3':
      if(l2-l1 >= interval){
      pixels1.setPixelColor(3,255,0,0);
      pixels2.setPixelColor(3,255,0,0);
      pixels4.setPixelColor(3,255,0,0);
      pixels1.show();
      pixels2.show();
      pixels4.show();
      pixels3.clear();
      l1=l2;
      Time3++;
      if(Time3<=10){  //10초동안 초록색 파란색 LED ON
        pixels3.setPixelColor(0,0,255,0);
        pixels3.setPixelColor(1,0,0,255);
        pixels3.show();
        if(Time3>5)   //딜레마
          callD(512,3); 
        }else if(Time3>10 && Time3 <= 15){ //10초부터 5초동안 주황색 LED ON
          pixels3.clear(); 
          pixels3.setPixelColor(2,255,215,0);
          pixels3.show();
        }else{
          pixels3.setPixelColor(3,255,0,0);
          pixels3.show();
          Wire.write('3');
          l1=0;
          Time4=0;
          break;
        }
      }
    case '4':
    if(l2-l1 >= interval){
      pixels1.setPixelColor(3,255,0,0);
      pixels2.setPixelColor(3,255,0,0);
      pixels3.setPixelColor(3,255,0,0);
      pixels1.show();
      pixels2.show();
      pixels3.show();
      pixels4.clear();
      l1=l2;
      Time4++;
      if(Time4<= 10){
        pixels4.setPixelColor(0,0,255,0);
        pixels4.setPixelColor(1,0,0,255);
        pixels4.show();
        if(Time4>5)
          callD(512,4);
        }else if(Time4>10 && Time4 <= 15){
          pixels4.clear();
          pixels4.setPixelColor(2,255,215,0);
          pixels4.show();
        }else{
          pixels4.setPixelColor(3,255,0,0);
          pixels4.show();
          Wire.write('0'); //송신
          l1=0;
          Time1=0;
          break;
       }
     }
  }
  Wire.endTransmission();
}

void callD(int wait,int i) { //깜박이는 함수
  switch(i){
    case 1:
    for (int b=0; b < 2; b++) {
        pixels5.clear();
        for (int c=b; c < 1; c=c+3) {
          pixels5.setPixelColor(0, 0,0,255);
          pixels5.setPixelColor(1, 0,0,255);
          pixels5.setPixelColor(2, 0,0,255);
          pixels5.setPixelColor(3, 0,0,255);
          pixels5.setPixelColor(4, 0,0,255); 
          pixels5.setPixelColor(5, 0,0,255); 
          pixels5.setPixelColor(6, 0,0,255); 
          pixels5.setPixelColor(7, 0,0,255); 
        }
        pixels5.show();
        delay(wait);
    }
    break;
    case 2:
    for (int b=0; b < 2; b++) {
        pixels6.clear();
        for (int c=b; c < 1; c=c+3) {
          pixels6.setPixelColor(0, 0,0,255); 
          pixels6.setPixelColor(1, 0,0,255); 
          pixels6.setPixelColor(2, 0,0,255); 
          pixels6.setPixelColor(3, 0,0,255); 
          pixels6.setPixelColor(4, 0,0,255); 
          pixels6.setPixelColor(5, 0,0,255); 
          pixels6.setPixelColor(6, 0,0,255); 
          pixels6.setPixelColor(7, 0,0,255); 
      }
        pixels6.show();
        delay(wait);
    }
    break;
    case 3:
    for (int b=0; b < 2; b++) {
        pixels7.clear();
        for (int c=b; c < 1; c=c+3) {
          pixels7.setPixelColor(0, 0,0,255); 
          pixels7.setPixelColor(1, 0,0,255); 
          pixels7.setPixelColor(2, 0,0,255); 
          pixels7.setPixelColor(3, 0,0,255); 
          pixels7.setPixelColor(4, 0,0,255); 
          pixels7.setPixelColor(5, 0,0,255); 
          pixels7.setPixelColor(6, 0,0,255); 
          pixels7.setPixelColor(7, 0,0,255); 
      }
        pixels7.show();
        delay(wait);
    }
    break;
   case 4:
    for (int b=0; b < 2; b++) {
        pixels8.clear();
        for (int c=b; c < 1; c=c+3) {
          pixels8.setPixelColor(0, 0,0,255); 
          pixels8.setPixelColor(1, 0,0,255); 
          pixels8.setPixelColor(2, 0,0,255); 
          pixels8.setPixelColor(3, 0,0,255); 
          pixels8.setPixelColor(4, 0,0,255); 
          pixels8.setPixelColor(5, 0,0,255); 
          pixels8.setPixelColor(6, 0,0,255); 
          pixels8.setPixelColor(7, 0,0,255); 
      }
        pixels8.show();
        delay(wait);
    }
    break;
    }
}