#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>

//rx, tx : 13, 12

//모터 사용
Servo myservo_1;
Servo myservo_3;
int pos_1 = 0;
int pos_3 = 0;
int signal = 0;
int degree = 45;

//시간 측정
unsigned long l1 = 0, l2 = 0;
unsigned long interval = 1024;
int Time1, Time3;

//신호 및 통신
SoftwareSerial mySerial(12, 13); //시리얼 통신 핀
unsigned long Switch;
byte c;

//초음파 센서
const int pinTrig_1 = 4;
const int pinEcho_1 = 5;
const int pinTrig_3 = 7;
const int pinEcho_3 = 8;
int rangeMax = 200;
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
}

void loop()
{
    l2 = millis();

    if (mySerial.available() > 0) //데이터가 수신되는지 확인
    {
        char ch = mySerial.read(); //1바이트 읽음
        mySerial.println(ch);      //1바이트 읽은거 출력
    }

    //초음파 보내며, 다 보내면 echo가 HIGH(신호받기) 상태로 대기
    digitalWrite(pinTrig_1, LOW);
    digitalWrite(pinTrig_3, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrig_1, HIGH);
    digitalWrite(pinTrig_3, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrig_1, LOW);
    digitalWrite(pinTrig_3, LOW);

    T_1 = pulseIn(pinEcho_1, HIGH);
    T_3 = pulseIn(pinEcho_3, HIGH);

    L_1 = T_1 / 58.82; //1번 초음파 센서로 거리 측정
    L_3 = T_3 / 58.82; //3번 초음파 센서로 거리 측정

    ///////////////////////////
    //딜레마존 구현부
    Time1 = 0;
    Time3 = 0;

    //차량이 범위내에 없으면
    if (L_1 < rangeMax)
    {
        //시간 측정
        if (l2 - l1 >= interval)
        {
            l1 = l2;
            Time1++;
            if (Time1 > 5)
            {
                //차량이 없으니 신호를 미리 바꿔도 된다는 신호 전송
                mySerial.write('불켜');
            }
        }
    }
    if (!(L_3 < rangeMax))
    {
        //시간 측정
        if (l2 - l1 >= interval)
        {
            l1 = l2;
            Time3++;
            if (Time3 > 5)
            {
                //차량이 없으니 신호를 미리 바꿔도 된다는 신호 전송
                mySerial.write('불켜');
            }
        }
    }

    ///////////////////////////
    //바리게이트 작동 구현부
    switch (signal)
    {
    case 1:
        if (l2 - l1 >= interval)
        {
            l1 = l2;
            Time1++;
            if (Time1 >= 1 && Time1 < 2)
            {
                //1번 바리게이트 올라옴
                for (pos_1 = 0; pos_1 <= degree; pos_1 += 1)
                {
                    myservo_1.write(pos_1);
                }
            }
            else if (Time1 >= 3)
            {
                //1번 바리게이트 내려옴
                for (pos_1 = 0; pos_1 <= degree; pos_1 -= 1)
                {
                    myservo_1.write(pos_1);
                }
            }
        }
        break;
    case 3:
        if (l2 - l1 >= interval)
        {
            l1 = l2;
            Time3++;
            if (Time3 >= 1 && Time3 < 2)
            {
                //1번 바리게이트 올라옴
                for (pos_3 = 0; pos_3 <= degree; pos_3 += 1)
                {
                    myservo_3.write(pos_3);
                }
            }
            else if (Time1 >= 3)
            {
                //1번 바리게이트 내려옴
                for (pos_3 = 0; pos_3 <= degree; pos_3 -= 1)
                {
                    myservo_3.write(pos_3);
                }
            }
        }
        break;
    }
}