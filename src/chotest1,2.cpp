#include <Servo.h>
#include <SoftwareSerial.h>
#include <SPI.h>

//RX(수신), TX(송신) : 0,1
//시간 측정
unsigned long l1 = 0, l2 = 0, l3 = 0, l4 = 0, l5 = 0, l6 = 0;
unsigned long interval = 512;
int Time1, Time2;

//신호 및 통신
SoftwareSerial mySerial(3, 9); //시리얼 통신 핀
volatile byte command = 0;
volatile byte Signal = 0;
byte s;
int A = 0, B = 0, C = 0, D = 0;

//초음파 센서
const int pinTrig_2 = 4;
const int pinEcho_2 = 5;
const int pinTrig_1 = 7;
const int pinEcho_1 = 8;
long T_2, T_1;
long L_2, L_1;
byte c = 0;
byte light;
byte num;
char check = 0;

void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600);

    Time1 = 0;
    Time2 = 0;

    //초음파 센서
    pinMode(pinTrig_1, OUTPUT);
    pinMode(pinEcho_1, INPUT);
    pinMode(pinTrig_2, OUTPUT);
    pinMode(pinEcho_2, INPUT);

    //SPI 통신
    SPI.setClockDivider(SPI_CLOCK_DIV16);
    pinMode(MISO, OUTPUT);
    SPCR |= _BV(SPE);
    SPCR |= _BV(SPIE);
    SPCR &= ~_BV(MSTR);
}

ISR(SPI_STC_vect)
{
    byte Signal = SPDR;
    switch (command)
    {
    case 0:
        command = Signal;
        SPDR = 0;
        break;
    case 'a':
        SPDR = c;
        num = 'a';
        break;
    case 'b':
        SPDR = c;
        num = 'b';
        break;
    case 'c':
        SPDR = c;
        num = 'c';
        break;
    case 'd':
        SPDR = c;
        num = 'd';
        break;
    }
}

void loop()
{

    //    l2 = millis();
    //    if (l2 - l1 >= interval)
    //    {
    //        l1 = l2;

    if (mySerial.available())
    {
        s = mySerial.read();
        if (s == '3' || s == '4')
        {

            if (s == '3')
            {
                c = s;
                Serial.println("3번 패스");
            }
            else if (s == '4')
            {
                if (s == '4')
                {
                    c = s;
                    Serial.println("4번 패스");
                }
            }
        }
    }

    if (num == 'a' || num == 'b' || num == 'c' || num == 'd')
    {
        mySerial.write(num);
    }

    //2번 초음파 보내며, 다 보내면 echo가 HIGH(신호받기) 상태로 대기
    digitalWrite(pinTrig_2, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrig_2, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrig_2, LOW);

    T_2 = pulseIn(pinEcho_2, HIGH);

    L_2 = T_2 / 58.82; //2번 초음파 센서로 거리 측정

    //1번 초음파 보내며, 다 보내면 echo가 HIGH(신호받기) 상태로 대기
    digitalWrite(pinTrig_1, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrig_1, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrig_1, LOW);

    T_1 = pulseIn(pinEcho_1, HIGH);

    L_1 = T_1 / 58.82; //1번 초음파 센서로 거리 측정

    check = num;
    Serial.print("현재 신호 : ");
    Serial.println(check);
    Serial.print("1번 신호 :");
    Serial.println(L_1);
    Serial.print("2번 신호 : ");
    Serial.println(L_2);
    Serial.println("----------------------");

    ///////////////////////////
    //시간절약 구현부
    //통신은 I2C 사용
    //차량이 범위내에 없으면

    switch (num)
    {
    case 'a': //1번 신호등이 초록불이고 일정 시간 이상 아무것도 없으면 3번 신호등 바꿔도 된다는 신호 전송
        if (!(L_2 < 8))
        {
            l4 = millis();
            //2초가 지날때까지 차가 감지 되지 않으면 바꿔도 된다는 신호 전송
            //시간 측정
            if (l4 - l3 >= interval)
            {

                l3 = l4;
                Time2++;

                if (Time2 >= 1)
                {
                    //차량이 없으니 신호를 미리 바꿔도 된다는 신호 전송
                    Serial.println("2번 패스");
                    c = '2';
                    Time2 = 0;
                    l3 = 0;
                }
            }
        }

    case 'd': //4번 신호등이 초록불이고 일정 시간 이상 아무것도 없으면 2번 신호등 바꿔도 된다는 신호 전송
        if (!(L_1 < 8))
        {

            l6 = millis();
            //2초가 지날때까지 차가 감지 되지 않으면 바꿔도 된다는 신호 전송

            //시간 측정
            if (l6 - l5 >= interval)
            {

                l5 = l6;
                Time1++;
                if (Time1 > 1)
                {
                    //차량이 없으니 신호를 미리 바꿔도 된다는 신호 전송
                    //4번 바리 - 1번 초음파
                    Serial.println("1번 패스");

                    c = '1';
                    Time1 = 0;
                    l5 = 0;
                }
            }
        }
    }
    if (digitalRead(SS) == HIGH)
        command = 0;
    //    }
}