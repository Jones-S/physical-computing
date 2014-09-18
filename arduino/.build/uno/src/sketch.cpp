#include <Arduino.h>

void setup();
void loop();
#line 1 "src/sketch.ino"
#define buttonPin 10 //input button
#define led 11 //define led

int minimumTime = 50;
int pauseTime = 1500;
int buttonPressed = false;
boolean change;
boolean actualState = 0;
int duration = 0; //button Press duration
int start = 0;
int pressTime;
int lastClick = 0;
int click;
int pressCounter = 0;

int parrotStorage[20];

void setup()
{
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(led, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    // change digitalRead to more readable Format
    actualState = !digitalRead(buttonPin);


    //check state vs. actual state & check if not flicker
    if (buttonPressed != actualState)
    {
        lastClick = click;
        click = millis();
        if(click - lastClick > minimumTime){
          change = true;
        }
    }



    if (change && actualState)  //if button is down and a change happened
    {
        change = false;
        // if long enough start time
        start = millis(); //save current time in start
    }
    else if (change && !actualState) //if button up and change happened
    {
        change = false;
        duration = millis() - start; //save duration by subtracting start from millis

        //check if button was pressed for a satisfying duration
        if (duration > minimumTime)
        {
            //save duration in array
            parrotStorage[pressCounter] = duration;
            Serial.println(parrotStorage[pressCounter]);
            pressCounter++;
        }
        else
        {
            //discard duration
            Serial.println("not recorded");
        }
    }

    //check if recording should be finished
    if ((millis() - click) > pauseTime)
    {
        //stop recording and play it
        for (int i = 0; i < pressCounter; i++)
        {
            digitalWrite(led, HIGH);
            delay(parrotStorage[i]);
            digitalWrite(led, LOW);
            delay(400);
            parrotStorage[i] = 0;

        }

        lastClick, click, pressCounter = 0;

    }




    buttonPressed = actualState;




}