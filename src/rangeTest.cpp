const int pinTrig = 2;
const int pinEcho = 4;
int rangeMax = 200;
int rangeMin = 0;
long T, L;
void setup()
{
    Serial.begin(9600);
    pinMode(pinTrig, OUTPUT);
    pinMode(pinEcho, INPUT);
}
void loop()
{
    digitalWrite(pinTrig, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrig, LOW);
    T = pulseIn(pinEcho, HIGH);
    L = T / 58.82;
    if (L >= rangeMax || L <= rangeMin)
        Serial.println("-1");
    else
        Serial.println(L);
    delay(100);
}
const int pinTrig = 2;
const int pinEcho = 4;
int rangeMax = 200;
int rangeMin = 0;
long T, L;
void setup()
{
    Serial.begin(9600);
    pinMode(pinTrig, OUTPUT);
    pinMode(pinEcho, INPUT);
}
void loop()
{
    digitalWrite(pinTrig, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrig, LOW);
    T = pulseIn(pinEcho, HIGH);
    L = T / 58.82;
    if (L >= rangeMax || L <= rangeMin)
        Serial.println("-1");
    else
        Serial.println(L);
    delay(100);
}