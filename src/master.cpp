#include <SPI.h>
const int s1 = 10;
const int s2 = 9;
int mode = 0;
byte c, s;

//시간 측정
unsigned long l1 = 0, l2 = 0;
unsigned long interval = 512;
double Time;
void setup()
{
    Serial.begin(9600);
    SPI.begin();
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    digitalWrite(s1, HIGH);
    digitalWrite(s2, HIGH);
    SPI.setClockDivider(SPI_CLOCK_DIV16);
    Time = 0;
    l1 = 0;
}
byte transferAndWait(const byte what)
{
    byte a = SPI.transfer(what);
    delayMicroseconds(20);
    return a;
}
void loop()
{
    l2 = millis();

    if (l2 - l1 >= interval)
    {
        l1 = l2;
        digitalWrite(s1, LOW);
        transferAndWait('c');
        transferAndWait(0);
        c = transferAndWait(0);
        digitalWrite(s1, HIGH);

        Serial.println(c);
        digitalWrite(s2, LOW);

        switch (c)
        {
        case '1':
            transferAndWait('a');
            transferAndWait(0);
            break;
        case '2':
            transferAndWait('b');
            transferAndWait(0);
            break;
        case '3':
            transferAndWait('c');
            transferAndWait(0);
            break;
        case '4':
            transferAndWait('d');
            transferAndWait(0);
            break;
        }
        digitalWrite(s2, HIGH);
    }
}