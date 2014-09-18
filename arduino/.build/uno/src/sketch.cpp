#include <Arduino.h>

void setup();
void loop();
#line 1 "src/sketch.ino"
int ledPin = 10;
unsigned int i = 0;
boolean rise = true;
int period = 1000;
void setup()
{
    pinMode(ledPin, OUTPUT);
}
void loop()
{
    if (i == period)
    {
        i = 1;
        rise = !rise;
    }
    if (rise == false)
    {
        digitalWrite(ledPin, LOW);
        delayMicroseconds(i);
        digitalWrite(ledPin, HIGH);
        delayMicroseconds(period - i);
        i = i + 1;
    }
    if (rise == true)
    {
        digitalWrite(ledPin, LOW);
        delayMicroseconds(period - i);
        digitalWrite(ledPin, HIGH);
        delayMicroseconds(i);
        i = i + 1;
    }
}