#include <SPI.h>
const int s1 = 10; //신호등
const int s2 = 9;  //바게트
byte c;
byte signal;

void setup()
{
    Serial.begin(9600);

    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV16);
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    digitalWrite(S1, HIGH);
    digitalWrite(S2, HIGH);
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
    transferAndWait('c');
    transferAndWait(0);
    c = transferAndWait(0);
    digitalWrite(S1, HIGH);

    digitalWrite(s2, LOW);
    transferAndWait('signal');
    transferAndWait(0);
    signal = transferAndWait(0);
    digitalWrite(S2, HIGH);

    if (c == '1')
    {
    }
}

ISR(SPI_STC_vect)
{
    byte c = SPDR;
    switch (command)
    {
    case 0:
        command = c;
        SPDR = 0;
        break;
    case 's':
        SPDR = data;
        break;
    }
}
void loop()
{
    data = (byte)random(0, 100);
    if (digitalRead(SS) == HIGH)
        command = 0;
}