#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <SPI.h>

//RX(수신), TX(송신) : 0,1

//모터 사용
Servo myservo_1;
Servo myservo_3;
int pos_1 = 0;
int pos_3 = 0;
int degree = 90;

//시간 측정
unsigned long l1 = 0, l2 = 0;
unsigned long interval = 1024;
int Time1, Time3;

//신호 및 통신
SoftwareSerial mySerial(12, 13); //시리얼 통신 핀
unsigned long Switch;
byte signal;

//SPI 통신
char buf[100];
volatile byte pos = 0;
volatile boolean done = false;

//초음파 센서
const int pinTrig_1 = 4;
const int pinEcho_1 = 5;
const int pinTrig_3 = 7;
const int pinEcho_3 = 8;
int rangeMax = 50;
int rangeMin = 0;
long T_1, T_3;
long L_1, L_3;

void setup()
{
    mySerial.begin(9600);
    Time1 = 0;
    Time3 = 0;
    l1 = 0;

    //모터 사용
    myservo_1.attach(2);
    myservo_3.attach(6);

    //초음파 센서
    pinMode(pinTrig_1, OUTPUT);
    pinMode(pinEcho_1, INPUT);
    pinMode(pinTrig_3, OUTPUT);
    pinMode(pinEcho_3, INPUT);

    //SPI 통신
    SPI.setClockDivider(SPI_CLOCK_DIV16);
    pinMode(MISO, OUTPUT);
    SPCR |= _BV(SPE);
    SPCR |= _BV(SPIE);
    SPCR &= ~_BV(MSTR);
}

ISR(SPI_STC_vect)
{
    byte c = SPDR;
    if (pos < sizeof(buf))
    {
        buf[pos++] = c;
        if (c == '\n')
            done = true;
    }
}

void loop()
{
    if (done)
    { // 마스터
        buf[pos] = 0;
        pos = 0;
        done = false;
    }
    l2 = millis();

    //1번 초음파 보내며, 다 보내면 echo가 HIGH(신호받기) 상태로 대기
    digitalWrite(pinTrig_1, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrig_1, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrig_1, LOW);

    T_1 = pulseIn(pinEcho_1, HIGH);

    //3번 초음파 보내며, 다 보내면 echo가 HIGH(신호받기) 상태로 대기
    digitalWrite(pinTrig_3, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrig_3, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrig_3, LOW);

    T_3 = pulseIn(pinEcho_3, HIGH);

    L_1 = T_1 / 58.82; //1번 초음파 센서로 거리 측정
    L_3 = T_3 / 58.82; //3번 초음파 센서로 거리 측정

    ///////////////////////////
    //시간절약 구현부
    //통신은 I2C 사용
    //차량이 범위내에 없으면
    if (L_1 < rangeMax)
    {
        //5초가 지날때까지 차가 감지 되지 않으면 바꿔도 된다는 신호 전송
        Time1 = 0;
        //시간 측정
        if (l2 - l1 >= interval)
        {
            l1 = l2;
            Time1++;
            if (Time1 > 5)
            {
                //차량이 없으니 신호를 미리 바꿔도 된다는 신호 전송
                mySerial.write('5');
            }
        }
    }
    if (!(L_3 < rangeMax))
    {
        //5초가 지날때까지 차가 감지 되지 않으면 바꿔도 된다는 신호 전송
        Time3 = 0;
        //시간 측정
        if (l2 - l1 >= interval)
        {
            l1 = l2;
            Time3++;
            if (Time3 > 5)
            {
                //차량이 없으니 신호를 미리 바꿔도 된다는 신호 전송
                mySerial.write('7');
            }
        }
    }

    ///////////////////////////
    //바리게이트 작동 구현부
    //UART 통신 사용?
    //마스터한테 바리게이트 올려 신호 받으면 올리기
    switch (signal)
    {
    case '1':
        if (l2 - l1 >= interval)
        {
            l1 = l2;
            Time1++;
            //1번 바리게이트 올라옴
            if (Time1 < 2)
            {
                myservo_1.write(180);
            }
            //1번 바리게이트 내려옴
            else if (Time1 > 4 && Time1 <= 6)
            {
                myservo_1.write(90);
            }
            else if (Time1 > 6)
            {
                Time3 = 0;
            }
            break;
        }
    case '3':
        if (l2 - l1 >= interval)
        {
            l1 = l2;
            Time3++;
            //3번 바리게이트 올라옴
            if (Time3 < 2)
            {
                myservo_3.write(180);
            }
            //1번 바리게이트 내려옴
            else if (Time3 > 4 && Time3 <= 6)
            {
                myservo_3.write(90);
            }
            else if (Time3 > 6)
            {
                Time1 = 0;
            }
            break;
        }
    }
}