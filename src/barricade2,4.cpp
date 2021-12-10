#include <Servo.h>
#include <SoftwareSerial.h>
#include <SPI.h>

//RX(수신), TX(송신) : 0,1

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
//SoftwareSerial mySerial(12, 13); //시리얼 통신 핀
unsigned long Switch;
volatile byte command = 0;
volatile byte data = 0;
byte Signal = 0;

//SPI 통신
char buf[100];
volatile byte pos = 0;
volatile boolean done = false;

void setup()
{
    Serial.begin(9600);
    Time2 = 0;
    Time4 = 0;
    l1 = 0;

    //모터 사용
    myservo_2.attach(2);
    myservo_4.attach(6);

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
    case '2':
        SPDR = data;
        break;
    case '4':
        SPDR = data;
        break;
    }
}

void loop()
{
    l2 = millis();
    ///////////////////////////
    //바리게이트 작동 구현부
    //UART 통신 사용?
    //마스터한테 바리게이트 올려 신호 받으면 올리기
    switch (Signal)
    {
    case '2':
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
    case '4':
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