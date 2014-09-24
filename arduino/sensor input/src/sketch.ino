
#define PONT A0

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	int value = analogRead(PONT);
	Serial.print(value);
	Serial.print(", 18,");
	Serial.println();
}
