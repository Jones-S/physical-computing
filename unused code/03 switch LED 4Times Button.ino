#define buttonPin 10 //input button
#define led 11 //define led
#define ledRed 9

boolean button_pressed = 0;
int press_counter = 0;
boolean state = 0; // 0 or 1

void setup()
{
    pinMode(buttonPin, INPUT);
    digitalWrite(buttonPin, HIGH); //pull up resistor activated
    pinMode(led, OUTPUT);
    pinMode(ledRed, OUTPUT);
    Serial.begin(9600);
}

void loop()
{

    if (button_pressed != digitalRead(buttonPin)) //if state different to button_pressed
    {
        Serial.println(press_counter);
        press_counter++;
    }
    
    if (press_counter > 7)
    {
        press_counter = 0; //reset
        state = !state;
        // Serial.println(state);
    }

    digitalWrite(led, !state);
    digitalWrite(ledRed, state);
    button_pressed = digitalRead(buttonPin); //save state in button_pressed
    Serial.println(press_counter);
}