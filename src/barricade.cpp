#include <Arduino.h>
#include <Servo.h>

//모터 사용
Servo myservo_1;
Servo myservo_2;
int pos_1 = 0;
int pos_2 = 0;

int degree = 45;

//시간 측정
unsigned long l1, l2;
unsigned long interval = 1024;
int Time = 0;

//신호
unsigned long Switch;

//초음파 센서
const int pinTrig_1 = 4;
const int pinEcho_1 = 5;
const int pinTrig_2 = 7;
const int pinEcho_2 = 8;
int rangeMax = 200;
int rangeMin = 0;
long T_1, T_2;
long L_1, L_2;

void setup()
{
    Serial.begin(9600);

    //모터 사용
    myservo_1.attach(2);
    myservo_2.attach(6);

    //초음파 센서
    pinMode(pinTrig_1, OUTPUT);
    pinMode(pinEcho_1, INPUT);
    pinMode(pinTrig_2, OUTPUT);
    pinMode(pinEcho_2, INPUT);
}

void loop()
{
    l2 = millis();

    //초음파 보내며, 다 보내면 echo가 HIGH(신호받기) 상태로 대기
    digitalWrite(pinTrig_1, LOW);
    digitalWrite(pinTrig_2, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrig_1, HIGH);
    digitalWrite(pinTrig_2, HIGH);
    delayMicroseconds(10);

    T_1 = pulseIn(pinEcho_1, HIGH);
    T_2 = pulseIn(pinEcho_2, HIGH);

    L_1 = T_1 / 58.82; //1번 초음파 센서로 거리 측정
    L_2 = T_2 / 58.82; //2번 초음파 센서로 거리 측정

        if (신호 = 빨강불 신호)
    {
        //1번 바리게이트 올라옴
        for (pos_1 = 0; pos_1 <= degree; pos_1 += 1)
        {
            myservo_1.write(pos_1);
        }
        //1번 바리게이트 내려옴
        for (pos_1 = 0; pos_1 <= degree; pos_1 -= 1)
        {
            myservo_1.write(pos_1);
        }
    }
    if (신호 = 빨강불 신호)
    {
        //2번 바리게이트 올라옴
        for (pos_2 = 0; pos_2 <= degree; pos_2 += 1)
        {
            myservo_2.write(pos_2);
        }
        //2번 바리게이트 내려옴
        for (pos_2 = 0; pos_2 <= degree; pos_2 -= 1)
        {
            myservo_2.write(pos_2);
        }
    }
}
}
