#include <Servo.h>
#include <SoftwareSerial.h>
#include <SPI.h>

//RX(수신), TX(송신) : 0,1
//시간 측정
unsigned long l1 = 0, l2 = 0, l3 = 0, l4 = 0, l5 = 0, l6 = 0;
unsigned long interval = 512;
int Time3, Time4;

//신호 및 통신
SoftwareSerial mySerial(3, 9); //시리얼 통신 핀
volatile byte command = 0;
volatile byte Signal = 0;
byte s;
int A = 0, B = 0, C = 0, D = 0;

//초음파 센서
const int pinTrig_3 = 4;
const int pinEcho_3 = 5;
const int pinTrig_4 = 7;
const int pinEcho_4 = 8;
long T_4, T_3;
long L_4, L_3;
byte light;
byte num = 0;

void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600);

    Time3 = 0;
    Time4 = 0;

    //초음파 센서
    pinMode(pinTrig_3, OUTPUT);
    pinMode(pinEcho_3, INPUT);
    pinMode(pinTrig_4, OUTPUT);
    pinMode(pinEcho_4, INPUT);
}

void loop()
{
    //    l2 = millis();
    //    if (l2 - l1 >= interval)
    //    {
    //        l1 = l2;
    if (mySerial.available() > 0)
    {
        num = mySerial.read();
    }

    //4번 초음파 보내며, 다 보내면 echo가 HIGH(신호받기) 상태로 대기
    digitalWrite(pinTrig_4, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrig_4, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrig_4, LOW);

    T_4 = pulseIn(pinEcho_4, HIGH);

    L_4 = T_4 / 58.82; //4번 초음파 센서로 거리 측정

    //3번 초음파 보내며, 다 보내면 echo가 HIGH(신호받기) 상태로 대기
    digitalWrite(pinTrig_3, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrig_3, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrig_3, LOW);

    T_3 = pulseIn(pinEcho_3, HIGH);

    L_3 = T_3 / 58.82; //3번 초음파 센서로 거리 측정

    Serial.print("3번 신호 :");
    Serial.println(L_3);
    Serial.print("4번 신호 : ");
    Serial.println(L_4);
    Serial.println("----------------------");

    ///////////////////////////
    //시간절약 구현부
    //통신은 I2C 사용
    //차량이 범위내에 없으면

    switch (num)
    {
    case 'b': //2번 신호등이 초록불이고 일정 시간 이상 아무것도 없으면 4번 신호등 바꿔도 된다는 신호 전송
        if (!(L_3 < 8))
        {

            l6 = millis();
            //2초가 지날때까지 차가 감지 되지 않으면 바꿔도 된다는 신호 전송

            //시간 측정
            if (l6 - l5 >= interval)
            {

                l5 = l6;
                Time3++;
                if (Time3 > 1)
                {
                    //차량이 없으니 신호를 미리 바꿔도 된다는 신호 전송
                    //2번 바리 - 3번 초음파
                    light = '3';
                    mySerial.write(light);
                    Time3 = 0;
                    l5 = 0;
                }
            }
        }

    case 'c': //3번 신호등이 초록불이고 일정 시간 이상 아무것도 없으면 1번 신호등 바꿔도 된다는 신호 전송
        if (!(L_4 < 8))
        {
            l4 = millis();
            //2초가 지날때까지 차가 감지 되지 않으면 바꿔도 된다는 신호 전송
            //시간 측정
            if (l4 - l3 >= interval)
            {

                l3 = l4;
                Time4++;

                if (Time4 > 1)
                {
                    //차량이 없으니 신호를 미리 바꿔도 된다는 신호 전송
                    //3번바리 - 4번 초음파

                    light = '4';
                    mySerial.write(light);
                    Time4 = 0;
                    l3 = 0;
                }
            }
        }
    }
    //    }
}