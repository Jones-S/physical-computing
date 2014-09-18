#include <Arduino.h>

void setup();
void loop();
#line 1 "src/sketch.ino"
#define buttonPin 10 //input button
#define led 11 //define led

boolean buttonOn = 0;
boolean stateChanged = false;

int press_counter = 0;
boolean state = 0; // 0 or 1
int button_storage[20][2]; //set up Array with 2 spots , two dimensional Array
int duration = 0; //storage for duration
int start = 0;

void setup()
{
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(led, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    if (buttonOn != digitalRead(buttonPin)) //if change had happened
    {
        //set flag
        stateChanged = true;
        Serial.println("Change");
        Serial.println(buttonOn);
    }

    if (stateChanged && buttonOn) //if button is down and it's the first loop since the press
    {
        start = millis();
        stateChanged = false;
        Serial.println("F");
    }
    else if (stateChanged && !buttonOn)     //if state changed and button released
    {
        duration = millis() - start;
        Serial.println(duration);
        stateChanged = false;
        Serial.println("F");

    }

    buttonOn = digitalRead(buttonPin); //save state



}