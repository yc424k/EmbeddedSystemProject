#include <Servo.h>
#include <SoftwareSerial.h>
#include <SPI.h>

//RX(수신), TX(송신) : 0,1

//모터 사용
Servo myservo_1;
Servo myservo_4;
int A = 0, D = 0;

//시간 측정
unsigned long l1 = 0, l2 = 0;
unsigned long l3 = 0, l4 = 0;
unsigned long interval = 1024;
int Time1, Time4;

//신호 및 통신
SoftwareSerial mySerial(3, 9); //시리얼 통신 핀
volatile byte command = 0;
volatile byte Signal = 0;
byte s;
byte num;

void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600);

    Time1 = 0;
    Time4 = 0;

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
    switch (command)
    {
    case 0:
        command = Signal;
        SPDR = 0;
        break;
    case 'a':
        num = 'a';
        break;
    case 'b':
        num = 'b';
        break;
    case 'c':
        num = 'c';
        break;
    case 'd':
        num = 'd';
        break;
    }
}

void loop()
{
    l4 = millis();
    if (l4 - l3 >= interval)
    {
        l3 = l4;
        mySerial.write(num);
    }
    if (num == 'a' || num == 'b' || num == 'c' || num == 'd')
    {
        mySerial.write(num);
        if (num == 'a' && A == 0)
            A = 1;
        else if (num == 'd' && D == 0)
            D = 1;
    }

    //    ///////////////////////////
    //    //바리게이트 작동 구현부
    //    //UART 통신 사용
    //    //마스터한테 바리게이트 올려 신호 받으면 올리기
    switch (num)
    {
    case 'a':
        l2 = millis();
        if (l2 - l1 >= interval)
        {
            if (A == 1)
            {
                l1 = l2;
                Time1++;
                if (Time1 > 0 && Time1 < 2)
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
                if (Time4 > 0 && Time4 < 2)
                {
                    myservo_4.write(90);
                }
                else
                {
                    myservo_4.write(180);
                    D++;
                    A = 0;
                    Time4 = 0;
                    break;
                }
            }
        }
    }
    if (digitalRead(SS) == HIGH)
        command = 0;
}