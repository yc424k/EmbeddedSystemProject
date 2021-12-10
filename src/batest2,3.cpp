#include <Servo.h>
#include <SoftwareSerial.h>
#include <SPI.h>

//RX(수신), TX(송신) : 0,1

//모터 사용
Servo myservo_2;
Servo myservo_3;
int pos_2 = 0;
int pos_3 = 0;
int degree = 90;
int B = 0, C = 0;
byte kind;

//시간 측정
unsigned long l1 = 0, l2 = 0, l3 = 0;
unsigned long interval = 1024;
int Time2, Time3;

//신호 및 통신
SoftwareSerial mySerial(3, 9); //시리얼 통신 핀
unsigned long Switch;
volatile byte command = 0;
volatile byte data = 0;
byte Signal = 0;
byte s;

//SPI 통신
char buf[100];
volatile byte pos = 0;
volatile boolean done = false;

void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600);

    //모터 사용
    myservo_2.attach(2);
    myservo_3.attach(6);
    myservo_2.write(180);
    myservo_3.write(180);
}

void loop()
{

    if (mySerial.available() > 0)
    {
        s = mySerial.read();
        Serial.print("신호 받았다 :");
        Serial.println(s);
    }

    if (s == 'a' || s == 'b' || s == 'c' || s == 'd')
    {
        kind = s;

        if (kind == 'b' && B == 0)
            B = 1;
        else if (kind == 'c' && C == 0)
            C = 1;
    }

    // mySerial.write(command);
    //    ///////////////////////////
    //    //바리게이트 작동 구현부
    //    //UART 통신 사용
    //    //마스터한테 바리게이트 올려 신호 받으면 올리기
    switch (kind)
    {
    case 'b':
        l2 = millis();
        if (l2 - l1 >= interval)
        {
            if (B == 1)
            {
                l1 = l2;
                Time2++;
                if (Time2 < 1)
                {
                    Serial.println("B확인");
                    myservo_2.write(180);
                }
                else if (Time2 >= 1 && Time2 < 3)
                {
                    myservo_2.write(90);
                }
                else
                {
                    myservo_2.write(180);
                    B++;
                    C = 0;
                    Time3 = 0;
                    break;
                }
            }
        }

    case 'c':
        l2 = millis();
        if (l2 - l1 >= interval)
        {
            if (C == 1)
            {
                l1 = l2;
                Time3++;
                if (Time3 < 1)
                {
                    Serial.println("C확인");
                    myservo_3.write(180);
                }
                else if (Time3 >= 1 && Time3 < 3)
                {
                    myservo_3.write(90);
                }
                else
                {
                    myservo_3.write(180);
                    C++;
                    B = 0;
                    Time2 = 0;
                    break;
                }
            }
        }
    }
}