
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
