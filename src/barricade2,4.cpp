#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <SPI.h>

//RX(수신), TX(송신) : 12, 13

//모터 사용
Servo myservo_2;
Servo myservo_4;
int pos_2 = 0;
int pos_4 = 0;
int degree = 90;

//시간 측정
unsigned long l1 = 0, l2 = 0;
unsigned long interval = 1024;
int Time2, Time4;

//신호 및 통신
SoftwareSerial mySerial(12, 13); //시리얼 통신 핀
unsigned long Switch;
byte signal;

//SPI 통신
volatile byte command = 0;

//초음파 센서
const int pinTrig_2 = 4;
const int pinEcho_2 = 5;
const int pinTrig_4 = 7;
const int pinEcho_4 = 8;
int rangeMax = 50;
int rangeMin = 0;
long T_2, T_4;
long L_2, L_4;

void setup()
{
    mySerial.begin(9600);
    Time2 = 0;
    Time4 = 0;
    l1 = 0;

    //모터 사용
    myservo_2.attach(2);
    myservo_4.attach(6);

    //초음파 센서
    pinMode(pinTrig_2, OUTPUT);
    pinMode(pinEcho_2, INPUT);
    pinMode(pinTrig_4, OUTPUT);
    pinMode(pinEcho_4, INPUT);
}

void loop()
{

    l2 = millis();

    //초음파 보내며, 다 보내면 echo가 HIGH(신호받기) 상태로 대기
    digitalWrite(pinTrig_2, LOW);
    digitalWrite(pinTrig_4, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrig_2, HIGH);
    digitalWrite(pinTrig_4, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrig_2, LOW);
    digitalWrite(pinTrig_4, LOW);

    T_2 = pulseIn(pinEcho_2, HIGH);
    T_4 = pulseIn(pinEcho_4, HIGH);

    L_2 = T_2 / 58.82; //2번 초음파 센서로 거리 측정
    L_4 = T_4 / 58.82; //4번 초음파 센서로 거리 측정

    ///////////////////////////
    //시간절약 구현부
    //통신은 I2C 사용
    //차량이 범위내에 없으면
    if (L_2 < rangeMax)
    {
        //5초가 지날때까지 차가 감지 되지 않으면 바꿔도 된다는 신호 전송
        Time2 = 0;
        //시간 측정
        if (l2 - l1 >= interval)
        {
            l1 = l2;
            Time2++;
            if (Time2 > 5)
            {
                //차량이 없으니 신호를 미리 바꿔도 된다는 신호 전송
                mySerial.write('불켜');
            }
        }
    }
    if (!(L_4 < rangeMax))
    {
        //5초가 지날때까지 차가 감지 되지 않으면 바꿔도 된다는 신호 전송
        Time4 = 0;
        //시간 측정
        if (l2 - l1 >= interval)
        {
            l1 = l2;
            Time4++;
            if (Time4 > 5)
            {
                //차량이 없으니 신호를 미리 바꿔도 된다는 신호 전송
                mySerial.write('불켜');
            }
        }
    }

    ///////////////////////////
    //바리게이트 작동 구현부
    //UART 통신 사용
    //마스터(1,3번 바리)한테 바리게이트 올려 신호 받으면 올리기
    if (mySerial.available())
    {
        signal = mySerial.read();
    }
    switch (signal)
    {
    case '1':
        if (l2 - l1 >= interval)
        {
            l1 = l2;
            Time2++;
            //2번 바리게이트 올라옴
            if (Time2 < 2)
            {
                myservo_2.write(180);
            }
            //2번 바리게이트 내려옴
            else if (Time2 > 4 && Time2 <= 6)
            {
                myservo_2.write(90);
            }
            else if (Time2 > 6)
            {
                Time4 = 0;
            }
            break;
        }
    case '3':
        if (l2 - l1 >= interval)
        {
            l1 = l2;
            Time4++;
            //4번 바리게이트 올라옴
            if (Time4 < 2)
            {
                myservo_4.write(180);
            }
            //4번 바리게이트 내려옴
            else if (Time4 > 4 && Time4 <= 6)
            {
                myservo_4.write(90);
            }
            else if (Time4 > 6)
            {
                Time2 = 0;
            }
            break;
        }
    }
}