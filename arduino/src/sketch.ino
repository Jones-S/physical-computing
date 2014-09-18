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

int parrotStorage[20][2]; // [][0] = duration, [][1] = LOW/HIGH

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



    if (change)  //if button is down and a change happened
    {
        change = false;
        // if long enough start time
        duration = millis() - lastClick; //save duration by subtracting lastClick from millis

        //check if button was pressed for a satisfying duration
        if (duration > minimumTime)
        {
            //save duration in array
            parrotStorage[pressCounter][0] = duration;
            parrotStorage[pressCounter][1] = !actualState;
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
            digitalWrite(led, parrotStorage[i][1]);
            delay(parrotStorage[i][0]);
            parrotStorage[i][0] = 0;
            parrotStorage[i][1] = 0;

        }

        lastClick = 0;
        click = 0; 
        pressCounter = 0;
        duration = 0;
        digitalWrite(led, LOW);

    }




    buttonPressed = actualState;




}