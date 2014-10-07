#define INPUT_INDUCTOR A1
#define INPUT_BUT1 3
#define INPUT_BUT2 5
#define LED 9


int inputInductor = 0;

boolean buttonState1;             // the current reading from the input pin
boolean buttonState2;             // the current reading from the input pin
boolean lastButtonState1 = LOW;   // the previous reading from the input pin
boolean lastButtonState2 = LOW;   // the previous reading from the input pin

//booleans for saving fails
boolean fail1 = 0;
boolean fail2 = 0;

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime1 = 0;     // the last time the input button 1 was toggled
long lastDebounceTime2 = 0;     // the last time the input button 2 was toggled
long debounceDelay = 50;        // the debounce time; increase if the output flickers

long lastButtonSignal1 = 0;     // vars for saving the time of the last button press-event
long lastButtonSignal2 = 0;
long lastSignal = 0;            // var for saving time of last inductor signal
int timeDifference = 0;         // var for saving the difference in time between newSignal and lastButtonSignal


void setup() {
    //start serial connection
    Serial.begin(9600);
    pinMode(INPUT_INDUCTOR, INPUT);
    pinMode(INPUT_BUT1, INPUT_PULLUP);
    pinMode(LED, OUTPUT);

}

void loop() {
    //read analog input (0 - 1023) from copper inductor
    inputInductor = analogRead(INPUT_INDUCTOR);

    // read the state of the switch into a local variable:
    int reading1 = !digitalRead(INPUT_BUT1); //reverse value because of pullup resistor: 0 if button is pressed
    int reading2 = !digitalRead(INPUT_BUT2); //reverse value because of pullup resistor: 0 if button is pressed


    //TODO: check highest peak signal
    if (inputInductor > 300) {
        lastSignal = millis();
        newSignal = true;
        Serial.print(inputInductor);
        Serial.print(" ################################");
        Serial.println();
    }



    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH),  and you've waited
    // long enough since the last press to ignore any noise:

    // If the switch changed, due to noise or pressing:
    if (reading1 != lastButtonState1) {
        // reset the debouncing timer
        lastDebounceTime1 = millis();
    }
    //same for switch 2
    if (reading2 != lastButtonState2) {
        // reset the debouncing timer
        lastDebounceTime2 = millis();
    }

    if ((millis() - lastDebounceTime1) > debounceDelay) {
        // whatever the reading is at, it's been there for longer
        // than the debounce delay, so take it as the actual current state:

        // if the button state has changed:
        if (reading1 != buttonState1) {
            buttonState1 = reading1; //change current state to (e.g.) HIGH
        }
        //check if button is HIGH -> save time to lastButtonSignal
        if (buttonState1) {
            lastButtonSignal1 = millis();
        }
    }
    //and same for switch2
    if ((millis() - lastDebounceTime2) > debounceDelay) {
        if (reading2 != buttonState2) {
            buttonState2 = reading2;
        }
        if (buttonState2) {
            lastButtonSignal2 = millis();
        }
    }

    //check if evaluation is necessary
    if(newSignal && lastButtonSignal1 > 0 && !fail1){
        evaluate ()
    }

    // save the reading.  Next time through the loop,
    // it'll be the lastButtonState:
    lastButtonState1 = reading1;
    lastButtonState2 = reading2;
}


//evaluation of time difference
int evaluate () {

}
