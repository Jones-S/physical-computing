
#define PONT A0

void setup()
{
	Serial.begin(9600);


void loop()
{
	int value = analogRead(PONT);
	Serial.println(value);

}
