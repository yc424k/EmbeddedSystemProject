//슬레이브
#include <SPI.h>

volatile byte command = 0;
volatile byte data = 0;

void setup()
{
    pinMode(MISO, OUTPUT);
    SPCR |= _BV(SPE);
    SPCR &= ~_BV(MSTR);
    SPCR |= _BV(SPIE);
}
ISR(SPI_STC_vect)
{
    byte c = SPDR;
    switch (command)
    {
    case '0':
        command = c;
        SPDR = 0;
        break;
    case 'c':
        SPDR = data;
        break;
    case 'signal':
        SPDR = data;
        break;
    }
}
void loop()
{
    data = '1';
    if (digitalRead(SS) == HIGH)
        command = 0;
}