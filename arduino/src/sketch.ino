#define buttonPin 10 //input button
#define led 11 //define led

int minimumTime = 50;
int buttonPressed = false;
boolean change;
boolean actualState = 0;
int duration = 0; //button Press duration
int start = 0;
int lastClick = 0;
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
        //example: if buttonPressed(true) == button HIGH (not pressed)
        //set flag
        change = true;
        lastClick = millis();
        //buttonPressed = actualState;
        // Serial.println("change");
    }

    if (change && lastClick > minimumTime && actualState)  //if button is down and a change happened
    {
        change = false;
        lastClick = 0;
        // if long enough start time
        start = millis(); //save current time in start
    }
    else if (change && lastClick > minimumTime && !actualState) //if button up and change happened
    {
        change = false;
        lastClick = 0;
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






    buttonPressed = actualState;
  



}