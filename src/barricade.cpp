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

void setup()
{
    Serial.begin(9600);

    //모터 사용
    myservo_1.attach(2);
    myservo_2.attach(2);
}

void loop()
{
    l2 = millis();
    if (신호 = 빨강불 신호)
        for (pos_1 = 0; pos_1 <= degree; pos_1 += 1)
        {
            myservo_1.write(pos_1);
        }
}
}
