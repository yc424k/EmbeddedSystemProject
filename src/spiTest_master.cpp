//마스터
#include <SPI.h>

const int S1 = 10; //신호등
const int S2 = 9;  //바게트
byte s;
byte Signal;

void setup()
{
    Serial.begin(9600);
    pinMode(S1, OUTPUT);
    digitalWrite(S1, HIGH);
    pinMode(S2, OUTPUT);
    digitalWrite(S2, HIGH);
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV16);
}

byte transferAndWait(const byte what)
{
    byte a = SPI.transfer(what);
    delayMicroseconds(20);
    return a;
}

void loop()
{

    digitalWrite(S1, LOW);
    transferAndWait('s');
    transferAndWait(0);
    s = transferAndWait(0);
    digitalWrite(S1, HIGH);

    if (s == '1')
    {
        digitalWrite(S2, LOW);
        transferAndWait('1');
        transferAndWait(0);
        Signal = transferAndWait(0);
        digitalWrite(S2, HIGH);
        delay(1000);
    }
}