#include <Servo.h>
#include <SoftwareSerial.h>
#include <SPI.h>

//RX(수신), TX(송신) : 0,1

//모터 사용
Servo myservo_1;
Servo myservo_4;
int pos_1 = 0;
int pos_3 = 0;
int degree = 90;
int mode = 0;
int A = 0, B = 0, C = 0, D = 0;

//시간 측정
unsigned long l1 = 0, l2 = 0;
unsigned long interval = 1024;
int Time1, Time4;

//신호 및 통신
SoftwareSerial mySerial(3, 9); //시리얼 통신 핀
unsigned long Switch;
volatile byte command = 0;
volatile byte data = 0;
byte Signal = 0;
byte s;
byte kind;

//초음파 센서
const int pinTrig_1 = 4;
const int pinEcho_1 = 5;
const int pinTrig_3 = 7;
const int pinEcho_3 = 8;
int rangeMax = 50;
int rangeMin = 0;
long T_1, T_3;
long L_1, L_3;

//SPI 통신
char buf[100];
volatile byte pos = 0;
volatile boolean done = false;

void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600);

    Time1 = 0;
    Time4 = 0;
    l1 = 0;

    //모터 사용
    myservo_1.attach(2);
    myservo_4.attach(6);
    myservo_1.write(180);
    myservo_4.write(180);

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
    command = Signal;
}

void loop()
{
    l2 = millis();
    //    if (mySerial.available())
    //    {
    //        s = mySerial.read();
    //    }

    if (command == 'a' || command == 'b' || command == 'c' || command == 'd')
    {
        kind = command;
        mySerial.write(kind);
        if (kind == 'a' && A == 0)
            A = 1;
        else if (kind == 'd' && D == 0)
            D = 1;
    }

    //    ///////////////////////////
    //    //바리게이트 작동 구현부
    //    //UART 통신 사용
    //    //마스터한테 바리게이트 올려 신호 받으면 올리기
    switch (kind)
    {
    case 'a':
        l2 = millis();
        if (l2 - l1 >= interval)
        {
            if (A == 1)
            {
                l1 = l2;
                Time1++;

                if (Time1 <= 1)
                {
                    Serial.println("A확인");
                    myservo_1.write(180);
                }
                else if (Time1 > 1 && Time1 < 3)
                {
                    myservo_1.write(90);
                }
                else
                {
                    myservo_1.write(180);
                    A++;
                    D = 0;
                    Time4 = 0;
                    break;
                }
            }
        }
    case 'd':
        l2 = millis();
        if (l2 - l1 >= interval)
        {
            if (D == 1)
            {
                l1 = l2;
                Time4++;
                if (Time4 < 1)
                {
                    Serial.println("D확인");
                    myservo_4.write(180);
                }
                else if (Time4 >= 1 && Time4 < 3)
                {
                    myservo_4.write(90);
                }
                else
                {
                    myservo_4.write(180);
                    D++;
                    A = 0;
                    Time1 = 0;
                    break;
                }
            }
        }
    }
    if (digitalRead(SS) == HIGH)
        command = 0;
}