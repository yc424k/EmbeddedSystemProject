#include <Adafruit_NeoPixel.h> //네오픽셀
#include <Wire.h> //I2C 통신
#define sv 8
#define PEO_PIN1 2 //횡단보도
#define PEO_PIN2 3
#define PEO_PIN3 4 
#define PEO_PIN4 5
#define PEO_PIN5 6
#define PEO_PIN6 7
#define PEO_PIN7 8 //딜레마
#define PEO_PIN8 9
unsigned long l1,l2;
unsigned long interval= 1024; //1초
int Time1;
byte c;
byte data; //마스터 한테 보낼 데이터
byte serial;
Adafruit_NeoPixel pixels1(2, PEO_PIN1, NEO_GRB + NEO_KHZ800);  //네오픽셀 초기화
Adafruit_NeoPixel pixels2(2, PEO_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3(2, PEO_PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels4(2, PEO_PIN4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels5(2, PEO_PIN5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels6(2, PEO_PIN6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels7(2, PEO_PIN7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels8(2, PEO_PIN8, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  Wire.onRequest(requestEvent);//보내겠다
  Wire.onReceive(receiveEvent);//받겠다
  Wire.begin(sv); //I2C 시작
  Time1=0;
  l1=0;
  pixels1.begin();  //네오픽셀 시작
  pixels2.begin();
  pixels3.begin();
  pixels4.begin();
  pixels5.begin();
  pixels6.begin();
  pixels7.begin();
  pixels8.begin();
  pixels1.setPixelColor(1,255,0,0);
  pixels2.setPixelColor(1,255,0,0);
  pixels3.setPixelColor(1,255,0,0);
  pixels4.setPixelColor(1,255,0,0);
  pixels5.setPixelColor(1,255,0,0);
  pixels6.setPixelColor(1,255,0,0);
  pixels7.setPixelColor(1,255,0,0);
  pixels8.setPixelColor(1,255,0,0);
  pixels1.show();  //네오픽셀 LED ON
  pixels2.show();
  pixels3.show();
  pixels4.show();
  pixels5.show();
  pixels6.show();
  pixels7.show();
  pixels8.show();
} 
void loop() {
  if(Serial.available()){
    serial= Serial.read();
    Serial.write(serial);
  }
  if(serial == '1')// 1을 치면 차량신호등에 1을 보내면서 신호등 시작
  {
    data='1';
    serial='10'; //오류 안나게 serial 값 변경
  }

  l2=millis();
  switch(c){
   case '1':
   data='2';
   Time1=0;
   break;
   case '2':
   data='3';
   Time1=0;
   break;
   case '3':
   data='4';
   Time1=0;
   break;
   case '0':
    if(l2-l1 >= interval){ //횡단보도 신호등 시작
      l1=l2;
      Time1++;
      pixels1.clear();  //네오픽셀 LED OFF
      pixels2.clear();
      pixels3.clear();
      pixels4.clear();
      pixels5.clear();
      pixels6.clear();
      pixels7.clear();
      pixels8.clear();
      if(Time1<=10){  //10초동안 초록색 LED ON
      pixels1.setPixelColor(0, 0,255,0);
        pixels2.setPixelColor(0, 0,255,0); 
        pixels3.setPixelColor(0, 0,255,0); 
        pixels4.setPixelColor(0, 0,255,0); 
        pixels5.setPixelColor(0, 0,255,0);
        pixels6.setPixelColor(0, 0,255,0); 
        pixels7.setPixelColor(0, 0,255,0); 
        pixels8.setPixelColor(0, 0,255,0);
        pixels1.show();
        pixels2.show();
        pixels3.show();
        pixels4.show();
        pixels5.show();
        pixels6.show();
        pixels7.show();
        pixels8.show();
        if(Time1>5) //깜빡
          callP(512);
      }else{
        pixels1.clear();  //네오픽셀 LED OFF
        pixels2.clear();
        pixels3.clear();
        pixels4.clear();
        pixels5.clear();
        pixels6.clear();
        pixels7.clear();
        pixels8.clear();
        pixels1.setPixelColor(0, 255,0,0); //빨간붕 on
        pixels2.setPixelColor(0, 255,0,0); 
        pixels3.setPixelColor(0, 255,0,0); 
        pixels4.setPixelColor(0, 255,0,0); 
        pixels5.setPixelColor(0, 255,0,0);
        pixels6.setPixelColor(0, 255,0,0); 
        pixels7.setPixelColor(0, 255,0,0); 
        pixels8.setPixelColor(0, 255,0,0);
        pixels1.show();
        pixels2.show();
        pixels3.show();
        pixels4.show();
        pixels5.show();
        pixels6.show();
        pixels7.show();
        pixels8.show();
        data='1';
        break;
      }
     }
  }
}

void callP(int wait) { //깜박이는 함수
      for (int b=0; b < 2; b++) { //b가 증가하면 깜박이는 시간이 길어진다
        pixels1.clear();
        pixels2.clear();
        pixels3.clear();
        pixels4.clear();
        pixels5.clear();
        pixels6.clear();
        pixels7.clear();
        pixels8.clear();
        for (int c=b; c < 1; c=c+3) {
          pixels1.setPixelColor(0, 0,255,0);
          pixels2.setPixelColor(0, 0,255,0); 
          pixels3.setPixelColor(0, 0,255,0); 
          pixels4.setPixelColor(0, 0,255,0); 
          pixels5.setPixelColor(0, 0,255,0);
          pixels6.setPixelColor(0, 0,255,0); 
          pixels7.setPixelColor(0, 0,255,0); 
          pixels8.setPixelColor(0, 0,255,0); 
      }
        pixels1.show();
        pixels2.show();
        pixels3.show();
        pixels4.show();
        pixels5.show();
        pixels6.show();
        pixels7.show();
        pixels8.show();
        delay(wait);
    }
}
void requestEvent() {
  Wire.write(data);
}
void receiveEvent(int howMany) {
  if(Wire.available()) {
    c = Wire.read();
  }
}