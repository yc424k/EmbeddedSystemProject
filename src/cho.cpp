#include <Servo.h>
#include <SoftwareSerial.h>
#include <SPI.h>

//RX(수신), TX(송신) : 0,1
//시간 측정
unsigned long l1 = 0, l2 = 0, l3 = 0, l4 = 0, l5 = 0, l6 = 0;
unsigned long interval = 1024;
int Time1, Time2, Time3, Time4;

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
int n1 = 0, n2 = 0;
int N1 = 0, N2 = 0;
byte light;
byte num;

void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600);

    Time1 = 0;
    Time2 = 0;
    Time3 = 0;
    Time4 = 0;
    l1 = 0;

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
        SPDR = light;
        num = 'a';
        break;
    case 'b':
        SPDR = light;
        num = 'b';
        break;
    case 'c':
        SPDR = light;
        num = 'c';
        break;
    case 'd':
        SPDR = light;
        num = 'd';
        break;
    }
}

void loop()
{
    //    if (mySerial.available())
    //    {
    //        s = mySerial.read();
    //    }

    if (num == 'a' || num == 'b' || num == 'c' || num == 'd')
    {
        mySerial.write(num);
        if (num == 'a' && A == 0)
        {
            A = 1;
        }
        else if (num == 'b' && B == 0)
        {
        }
        else if (num == 'c' && C == 0)
        {
        }
        else if (num == 'd' && D == 0)
        {
            D = 1;
        }
    }

    //2번 초음파 보내며, 다 보내면 echo가 HIGH(신호받기) 상태로 대기
    digitalWrite(pinTrig_2, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrig_2, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrig_2, LOW);

    T_2 = pulseIn(pinEcho_2, HIGH);

    //1번 초음파 보내며, 다 보내면 echo가 HIGH(신호받기) 상태로 대기
    digitalWrite(pinTrig_1, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrig_1, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrig_1, LOW);

    T_1 = pulseIn(pinEcho_1, HIGH);

    L_2 = T_2 / 58.82; //2번 초음파 센서로 거리 측정
    L_1 = T_1 / 58.82; //1번 초음파 센서로 거리 측정

    ///////////////////////////
    //시간절약 구현부
    //통신은 I2C 사용
    //차량이 범위내에 없으면
    if (!(L_2 < 8))
    {
        l3 = millis();
        //5초가 지날때까지 차가 감지 되지 않으면 바꿔도 된다는 신호 전송
        //시간 측정
        if (l3 - l5 >= interval)
        {

            l5 = l3;
            Time1++;
            if (Time1 <= 2)
            {
                if (n2 != 2 && N2 == 0)
                {
                    Serial.println("2번 초음파 작동중");
                    Serial.println(L_2);
                }
            }
            if (Time1 > 2)
            {
                //차량이 없으니 신호를 미리 바꿔도 된다는 신호 전송
                //1번 바리 - 2번 초음파
                if (n2 != 2 && N2 == 0)
                    Serial.println("2번 초음파 출동");
                n2 = 2;
                l5 = 0;
            }
        }
    }
    if (!(L_1 < 8))
    {

        l4 = millis();
        //5초가 지날때까지 차가 감지 되지 않으면 바꿔도 된다는 신호 전송

        //시간 측정
        if (l4 - l6 >= interval)
        {

            l6 = l4;
            Time4++;
            if (Time4 <= 2)
            {
                if (n1 != 2 && N1 == 0)
                {
                    Serial.println("1번 초음파 작동중");
                    Serial.println(L_1);
                }
            }
            if (Time4 > 2)
            {
                //차량이 없으니 신호를 미리 바꿔도 된다는 신호 전송
                //4번 바리 - 1번 초음파
                if (n1 != 2 && N1 == 0)
                    Serial.println("1번 초음파 출동");
                Time4 = 0;
                n1 = 1;
                l6 = 0;
            }
        }
    }

    //    ///////////////////////////
    //    //바리게이트 작동 구현부
    //    //UART 통신 사용
    //    //마스터한테 바리게이트 올려 신호 받으면 올리기
    l2 = millis();
    switch (num)
    {
    case 'a':
        if (l2 - l1 >= interval)
        {
            if (n2 == 2 && N2 == 0) //1번 바리 - 2번 초음파
            {
                Serial.println("2번 초음파 발사");

                light = '2';
                n2 = 0;
                N1 = 0;
            }

            if (A == 1)
            {

                l1 = l2;
                Time1++;
                if (Time1 <= 1)
                {
                }
                else if (Time1 > 1 && Time1 < 3)
                {
                }
                else
                {
                    A++;
                    l1 = 0;
                    D = 0;
                    Time4 = 0;
                    break;
                }
            }
        }

    case 'd':
        if (l2 - l1 >= interval)
        {
            if (D == 1)
            {
                l1 = l2;
                Time4++;
                if (Time4 < 1)
                {
                }
                else if (Time4 >= 1 && Time4 < 3)
                {
                }
                else
                {
                    if (n1 == 1 && N1 == 0) //4번바리 - 1번 초음파
                    {
                        Serial.println("1번 초음파 발사");
                        light = '1';
                        n1 = 0;
                        N1++;
                    }
                    if (N1 == 1)
                    {
                        Serial.println("1번 초음파 초기화");
                        light = 0;
                        N1++;
                    }
                    N2 = 0;
                    Time1 = 0;
                    l1 = 0;
                    A = 0;
                    D++;
                    break;
                }
            }
        }
    }
    if (digitalRead(SS) == HIGH)
        command = 0;
}