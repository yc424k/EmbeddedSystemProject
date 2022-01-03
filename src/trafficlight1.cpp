#include <Adafruit_NeoPixel.h> //네오픽셀
#include <Wire.h> //I2C 통신
#define sv 8
#define CAR_PIN1 2 //차량
#define CAR_PIN2 3
#define CAR_PIN3 4
#define CAR_PIN4 5
#define DLE_PIN1 6
#define DLE_PIN2 7
#define DLE_PIN3 8
#define DLE_PIN4 9
unsigned long l1,l2,l3,l4;
unsigned long interval= 512; //1초
int Time1,Time2,Time3,Time4;
int fON1=0;
int fON2=0;
int fON3=0;
int fON4=0;
volatile byte c;
byte s;
Adafruit_NeoPixel pixels1(4, CAR_PIN1, NEO_GRB + NEO_KHZ800);  //네오픽셀 초기화
Adafruit_NeoPixel pixels2(4, CAR_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3(4,CAR_PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels4(4, CAR_PIN4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels5(9, DLE_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels6(9, DLE_PIN2, NEO_GRB + NEO_KHZ800 );
Adafruit_NeoPixel pixels7(9, DLE_PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels8(9, DLE_PIN4, NEO_GRB + NEO_KHZ800);
volatile byte command =0;
volatile byte data=0;
void setup() {
  Wire.begin(); //I2C 시작
  Serial.begin(9600);
  Time1=0;
  Time2=0;
  Time3=0;
  Time4=0;
  l1=0;
  l3=0;
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
  pixels5.show();
  pixels6.show();
  pixels7.show();
  pixels8.show();
 
  Wire.write('0');
  pinMode(MISO,OUTPUT);
  SPCR |= _BV(SPE);
  SPCR &= ~_BV(SPIE);
  SPCR |= _BV(SPIE);
}

void loop() {
  Wire.beginTransmission(sv); //slave 한테 보내겠다고 하는 거
  Wire.requestFrom(sv,1); // 받겠다고 하는거 1바이트
  if(Wire.available()>0){
     s= Wire.read();
  }
  l2=millis();
  switch(s){
    case '1':
    if(l2-l1 >= interval){
    pixels2.setPixelColor(3,255,0,0);
    pixels3.setPixelColor(3,255,0,0);
    pixels4.setPixelColor(3,255,0,0);
    pixels2.show();
    pixels3.show();
    pixels4.show();
    pixels1.clear();  //네오픽셀 LED OFF
    l1=l2;
    Time1++;
    if(Time1<=12){  //10초동안 초록색 파란색 LED ON
      pixels1.setPixelColor(0,0,255,0);
      pixels1.setPixelColor(1,0,0,255);
      pixels1.show();
      if(Time1>6)
        callD(1);
      }else if(Time1>12 && Time1 <= 16){ //10초부터 5초동안 주황색 LED ON
        pixels5.clear();
        pixels1.clear(); 
        pixels1.setPixelColor(2,255,50,0);
        pixels1.show();
        pixels5.show();
      }else{
        pixels1.setPixelColor(3,255,0,0);
        pixels1.show();
        Wire.write('1');
        l1=0;
        Time2=0;
        Time3=0;
        Time4=0;
        data='1';
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
      if(Time2<= 12){
        pixels2.setPixelColor(0,0,255,0);
        pixels2.setPixelColor(1,0,0,255);
        pixels2.show();
        if(Time2>6)
          callD(2);
        }else if(Time2>12 && Time2 <= 16){
          pixels6.clear();
          pixels2.clear();
          pixels2.setPixelColor(2,255,50,0);
          pixels2.show();
          pixels6.show();
        }else{
          pixels2.setPixelColor(3,255,0,0);
          pixels2.show();
          Wire.write('2');
          l1=0;
          Time1=0;
          Time3=0;
          Time4=0;
          data='2';
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
      if(Time3<=12){  //10초동안 초록색 파란색 LED ON
        pixels3.setPixelColor(0,0,255,0);
        pixels3.setPixelColor(1,0,0,255);
        pixels3.show();
        if(Time3>6)
          callD(3);
        }else if(Time3>12 && Time3 <= 16){ //10초부터 5초동안 주황색 LED ON
          pixels7.clear();
          pixels3.clear(); 
          pixels3.setPixelColor(2,255,50,0);
          pixels3.show();
          pixels7.show();
        }else{
          pixels3.setPixelColor(3,255,0,0);
          pixels3.show();
          Wire.write('3');
          l1=0;
          Time1=0;
          Time2=0;
          Time4=0;
          data='3';
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
      if(Time4<= 12){
        pixels4.setPixelColor(0,0,255,0);
        pixels4.setPixelColor(1,0,0,255);
        pixels4.show();
        if(Time4>6)
          callD(4);
        }else if(Time4>12 && Time4 <= 16){
          pixels8.clear();
          pixels4.clear();
          pixels4.setPixelColor(2,255,50,0);
          pixels4.show();
          pixels8.show();
        }else{
          pixels4.setPixelColor(3,255,0,0);
          pixels4.show();
          Wire.write('0'); //송신
          l1=0;
          Time1=0;
          Time2=0;
          Time3=0;
          data='4';
          break;
       }
     }
  }
  Wire.endTransmission();
  if(digitalRead(SS) ==HIGH)
    command=0;
}

void callD(int i) { //깜박이는 함수
  l4=millis();
  switch(i){
    case 1:
    if(l4-l3 >= interval){
        l3=l4;
        if(!fON1){
          fON1=HIGH;
        }else{
          fON1 =LOW;
        }
        if(fON1 == HIGH){
          pixels5.setPixelColor(0, 255,255,0);
          pixels5.setPixelColor(1, 255,255,0); 
          pixels5.setPixelColor(2, 255,255,0); 
          pixels5.setPixelColor(3, 255,255,0); 
          pixels5.setPixelColor(4, 255,255,0);
          pixels5.setPixelColor(5, 255,255,0); 
          pixels5.setPixelColor(6, 255,255,0); 
          pixels5.setPixelColor(7, 255,255,0);
          pixels5.setPixelColor(8, 255,255,0);
          pixels5.show();
        }else{
          pixels5.setPixelColor(0, 0,0,0);
          pixels5.setPixelColor(1, 0,0,0); 
          pixels5.setPixelColor(2, 0,0,0); 
          pixels5.setPixelColor(3, 0,0,0); 
          pixels5.setPixelColor(4, 0,0,0);
          pixels5.setPixelColor(5, 0,0,0); 
          pixels5.setPixelColor(6, 0,0,0); 
          pixels5.setPixelColor(7, 0,0,0);
          pixels5.setPixelColor(8, 0,0,0);
          pixels5.show();
          l3=0;
        }
     }
    break;
    case 2:
    if(l4-l3 >= interval){
        l3=l4;
        if(!fON2){
          fON2 =HIGH;
        }else{
          fON2 =LOW;
        }
        if(fON2 == HIGH){
          pixels6.setPixelColor(0, 255,255,0);
          pixels6.setPixelColor(1, 255,255,0); 
          pixels6.setPixelColor(2, 255,255,0); 
          pixels6.setPixelColor(3, 255,255,0); 
          pixels6.setPixelColor(4, 255,255,0);
          pixels6.setPixelColor(5, 255,255,0); 
          pixels6.setPixelColor(6, 255,255,0); 
          pixels6.setPixelColor(7, 255,255,0);
          pixels6.setPixelColor(8, 255,255,0);
          pixels6.show();
        }else{
          pixels6.setPixelColor(0, 0,0,0);
          pixels6.setPixelColor(1, 0,0,0); 
          pixels6.setPixelColor(2, 0,0,0); 
          pixels6.setPixelColor(3, 0,0,0); 
          pixels6.setPixelColor(4, 0,0,0);
          pixels6.setPixelColor(5, 0,0,0); 
          pixels6.setPixelColor(6, 0,0,0); 
          pixels6.setPixelColor(7, 0,0,0);
          pixels6.setPixelColor(8, 0,0,0);
          pixels6.show();
          l3=0;
        }
     }
    break;
    case 3:
    if(l4-l3 >= interval){
        l3=l4;
        if(!fON3){
          fON3 =HIGH;
        }else{
          fON3 =LOW;
        }
        if(fON3 == HIGH){
          pixels7.setPixelColor(0, 255,255,0);
          pixels7.setPixelColor(1, 255,255,0); 
          pixels7.setPixelColor(2, 255,255,0); 
          pixels7.setPixelColor(3, 255,255,0); 
          pixels7.setPixelColor(4, 255,255,0);
          pixels7.setPixelColor(5,255,255,0); 
          pixels7.setPixelColor(6, 255,255,0); 
          pixels7.setPixelColor(7,255,255,0);
          pixels7.setPixelColor(8, 255,255,0);
          pixels7.show();
        }else{
          pixels7.setPixelColor(0, 0,0,0);
          pixels7.setPixelColor(1, 0,0,0); 
          pixels7.setPixelColor(2, 0,0,0); 
          pixels7.setPixelColor(3, 0,0,0); 
          pixels7.setPixelColor(4, 0,0,0);
          pixels7.setPixelColor(5, 0,0,0); 
          pixels7.setPixelColor(6, 0,0,0); 
          pixels7.setPixelColor(7, 0,0,0);
          pixels7.setPixelColor(8, 0,0,0);
          pixels7.show();
          l3=0;
        }
     }
    break;
   case 4:
    if(l4-l3 >= interval){
        l3=l4;
        if(!fON4){
          fON4 =HIGH;
        }else{
          fON4 =LOW;
        }
        if(fON4 == HIGH){
          pixels8.setPixelColor(0, 255,255,0);
          pixels8.setPixelColor(1, 255,255,0); 
          pixels8.setPixelColor(2, 255,255,0); 
          pixels8.setPixelColor(3, 255,255,0); 
          pixels8.setPixelColor(4, 255,255,0);
          pixels8.setPixelColor(5, 255,255,0); 
          pixels8.setPixelColor(6, 255,255,0); 
          pixels8.setPixelColor(7, 255,255,0);
          pixels8.setPixelColor(8, 255,255,0);
          pixels8.show();
        }else{
          pixels8.setPixelColor(0, 0,0,0);
          pixels8.setPixelColor(1, 0,0,0); 
          pixels8.setPixelColor(2, 0,0,0); 
          pixels8.setPixelColor(3, 0,0,0); 
          pixels8.setPixelColor(4, 0,0,0);
          pixels8.setPixelColor(5, 0,0,0); 
          pixels8.setPixelColor(6, 0,0,0); 
          pixels8.setPixelColor(7, 0,0,0);
          pixels8.setPixelColor(8, 0,0,0);
          pixels8.show();
          l3=0;
        }
     }
    break;
    }
    
}

ISR(SPI_STC_vect) {
  c = SPDR;
  switch (command) {
  case 0:
  command = c;
  SPDR = 0; 
  break;
  case 'c':
  SPDR = data;
  break; 
  }
}