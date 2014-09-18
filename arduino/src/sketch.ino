// Code from http://www.rngtng.com/2009/05/17/arduino-fade-and-pulse-a-led-with-just-using-a-digitalport/
//digitalWrite fading

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
        i = 1; //reset counter
        rise = !rise; //change rise to contrary
    }
    if (rise == false)
    {
        digitalWrite(ledPin, LOW);
        delayMicroseconds(i);
        digitalWrite(ledPin, HIGH);
        delayMicroseconds(period - i);
        i = i + 1; //prolong delay i
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