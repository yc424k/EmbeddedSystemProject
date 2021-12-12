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

    //1번 초음파 보내며, 다 보내면 echo가 HIGH(신호받기) 상태로 대기
    digitalWrite(pinTrig_1, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrig_1, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrig_1, LOW);

    T_1 = pulseIn(pinEcho_1, HIGH);

    //4번 초음파 보내며, 다 보내면 echo가 HIGH(신호받기) 상태로 대기
    digitalWrite(pinTrig_4, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrig_4, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrig_4, LOW);

    T_4 = pulseIn(pinEcho_4, HIGH);

    L_1 = T_1 / 58.82; //1번 초음파 센서로 거리 측정
    L_4 = T_4 / 58.82; //4번 초음파 센서로 거리 측정

    ///////////////////////////
    //시간절약 구현부
    //통신은 I2C 사용
    //차량이 범위내에 없으면
    if (L_1 < rangeMax)
    {

        l3 = millis();
        //5초가 지날때까지 차가 감지 되지 않으면 바꿔도 된다는 신호 전송
        //시간 측정
        if (l3 - l5 >= interval)
        {
            Serial.print("2번 초음파: ");
            Serial.println(L_1);
            l5 = l3;
            Time1++;
            if (Time1 > 2)
            {
                //차량이 없으니 신호를 미리 바꿔도 된다는 신호 전송
                Serial.println("다음으로");
                Time1 = 0;
                n = 2;
                l5 = 0;
            }
        }
    }
    if (L_4 < rangeMax)
    {

        l4 = millis();
        //5초가 지날때까지 차가 감지 되지 않으면 바꿔도 된다는 신호 전송

        //시간 측정
        if (l4 - l6 >= interval)
        {
            Serial.print("4번 초음파: ");
            Serial.println(L_4);
            light = '4';
            l6 = l4;
            Time4++;
            if (Time4 > 2)
            {
                //차량이 없으니 신호를 미리 바꿔도 된다는 신호 전송
                Serial.println("다음으로");

                Time4 = 0;
                n = 1;
                l6 = 0;
            }
        }
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