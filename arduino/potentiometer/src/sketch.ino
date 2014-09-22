
#define LED_PIN 4
#define LED2 9
#define INPUT_PIN 0

int inputVal = 0;

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(LED2, OUTPUT);
    Serial.begin(9600);

}

void loop()
{
	inputVal = analogRead(INPUT_PIN);

    digitalWrite(LED_PIN, HIGH);
    delay(inputVal);
    digitalWrite(LED_PIN, LOW);
    delay(inputVal);

    Serial.println(inputVal); 

    digitalWrite(LED2, HIGH);
}
