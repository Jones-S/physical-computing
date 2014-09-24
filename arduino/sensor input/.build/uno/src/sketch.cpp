#include <Arduino.h>

void setup();
void loop();
#line 1 "src/sketch.ino"

#define PONT A0

void setup()
{
	Serial.begin(9600);
	println(Serial.list());
}

void loop()
{
	int value = analogRead(PONT);
	Serial.println(value);

}
