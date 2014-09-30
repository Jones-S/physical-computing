#include <Arduino.h>

void setup();
void loop();
#line 1 "src/sketch.ino"

#define CTRLPIN 9

void setup()
{
    pinMode(CTRLPIN, OUTPUT);
}

void loop()
{
    digitalWrite(CTRLPIN, HIGH);
    delay(400);
    digitalWrite(CTRLPIN, LOW);
    delay(1200);
}
