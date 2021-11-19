#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(12, 13);
#define CAR_PIN1 2
#define CAR_PIN2 5
#define PEO_PIN1 3
#define PEO_PIN2 4
#define PEO_PIN3 6
#define PEO_PIN4 7
unsigned long l1,l2;
unsigned long interval= 1024;
int Time1,Time3,Time5;
byte c;
Adafruit_NeoPixel pixels1(4, CAR_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(4, CAR_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3(2, PEO_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels4(2, PEO_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels5(2, PEO_PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels6(2, PEO_PIN4, NEO_GRB + NEO_KHZ800);

void setup() {
  Time1=0;
  Time3=0;
  Time5=0;
  l1=0;
  mySerial.begin(9600);
  pixels1.begin();
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
  pixels1.show();
  pixels2.show();
  pixels3.show();
  pixels4.show();
  pixels5.show();
  pixels6.show();
}
void loop() {
  l2=millis();
  if (mySerial.available()) {
  c = mySerial.read();
  }
  switch(c){
  case '1':
    if(l2-l1 >= interval){
    l1=l2;
    Time1++;
    pixels1.clear();
    if(Time1<= 3){
      pixels1.setPixelColor(0,0,255,0);
      pixels1.setPixelColor(1,0,0,255);
      pixels1.show();
      }else if(Time1>3 && Time1 <= 5){
        pixels1.clear();
        pixels1.setPixelColor(2,255,215,0);
        pixels1.show();
      }else{
        pixels1.clear();
        pixels1.setPixelColor(3,255,0,0);
        pixels1.show();
        mySerial.write('2');
        l1=0;
        Time3=0;
        break;
      }
    }
    case '3':
    if(l2-l1 >= interval){
    l1=l2;
    Time3++;
    pixels2.clear();
    if(Time3<= 3){
      pixels2.setPixelColor(0,0,255,0);
      pixels2.setPixelColor(1,0,0,255);
      pixels2.show();
      }else if(Time3>3 && Time3 <= 5){
        pixels2.clear();
        pixels2.setPixelColor(2,255,215,0);
        pixels2.show();
      }else{
        pixels2.clear();
        pixels2.setPixelColor(3,255,0,0);
        pixels2.show();
        mySerial.write('4');
        l1=0;
        Time5=0;
        break;
      }
    }
    case '5':
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
      theaterChase(400);
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
      c='1';
      Time1=0;
      l1=0;
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