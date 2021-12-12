#include <SPI.h>
const int s1 = 10;
const int s2 = 9;
byte c = '0', s = '0';

//시간 측정
unsigned long l1 = 0, l2 = 0;
unsigned long interval = 128;
void setup()
{
    Serial.begin(9600);
    SPI.begin();
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    digitalWrite(s1, HIGH);
    digitalWrite(s2, HIGH);
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
    l2 = millis();

    if (l2 - l1 >= interval)
    {
        l1 = l2;
        digitalWrite(s1, LOW);
        if (s == '1')
        {
            Serial.println("1");
            transferAndWait('a');
        }
        else if (s == '2')
        {
            Serial.println("2");
            transferAndWait('b');
            transferAndWait(0);
        }
        else if (s == '3')
        {
            Serial.println("3");
            transferAndWait('d');
            transferAndWait(0);
        }
        else if (s == '4')
        {
            Serial.println("4");
            transferAndWait('e');
            transferAndWait(0);
        }
        transferAndWait(0);

        transferAndWait('c');
        transferAndWait(0);
        c = transferAndWait(0);

        digitalWrite(s1, HIGH);

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
        s = transferAndWait(0);
        digitalWrite(s2, HIGH);
    }
}