#define INPUT_INDUCTOR A1
#define INPUT_BUT1 3
#define INPUT_BUT2 5
#define LED 9


int inputInductor = 0;
int readings[2] = {0, 0};

// boolean buttonState1;                // the current reading from the input pin
// boolean buttonState2;                // the current reading from the input pin
boolean buttonStates[2];                // actual current button state without flickering
// boolean lastButtonState1 = LOW;          // the previous reading from the input pin
// boolean lastButtonState2 = LOW;          // the previous reading from the input pin
boolean lastButtonStates[2] = LOW;      // buttonStates from last loop
boolean newSignal = false;

//booleans for saving fails
// boolean fail1 = 0;
// boolean fail2 = 0;
boolean fails[2] = {0, 0};              // failure states in array


// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
// long lastDebounceTime1 = 0;          // the last time the input button 1 was toggled
// long lastDebounceTime2 = 0;          // the last time the input button 2 was toggled
long lastDebounceTimes[2] = {0, 0}; s
long debounceDelay = 50;                // the debounce time; increase if the output flickers

// long lastButtonSignal1 = 0;          // vars for saving the time of the last button press-event
// long lastButtonSignal2 = 0;
long lastButtonSignals[2] = {0, 0};
long lastSignal = 0;                    // var for saving time of last inductor signal
int timeDifference = 0;                 // var for saving the difference in time between newSignal and lastButtonSignal


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
    readings[0] = !digitalRead(INPUT_BUT1); //reverse value because of pullup resistor: 0 if button is pressed
    readings[1] = !digitalRead(INPUT_BUT2); //reverse value because of pullup resistor: 0 if button is pressed


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

    for (int i = 0; i < sizeof(readings) - 1; i++) {
        // If the switch changed, due to noise or pressing:
        if (readings[i] != lastButtonStates[i]) {
            // reset the debouncing timer
            lastDebounceTimes[i] = millis();
        }

        if ((millis() - lastDebounceTimes[i]) > debounceDelay) {
            // whatever the reading is at, it's been there for longer
            // than the debounce delay, so take it as the actual current state:

            // if the button state has changed:
            if (readings[i] != buttonStates[i]) {
                buttonStates[i] = readings[i]; //change current state to (e.g.) HIGH
            }

            //check if button is HIGH -> save time to lastButtonSignal
            if (buttonStates[i]) {
                lastButtonSignals[i] = millis();
            }
        }

        //check if evaluation is necessary
        if (newSignal && lastButtonSignals[i] > 0 && !fail[i]) { //only check if newSignal, button was pressed and there has not been a failure
            evaluate (lastButtonSignals[i], lastSignal)
        }
    }




    // save the reading.  Next time through the loop,
    // it'll be the lastButtonState:
    for(int i=0; i< sizeof(lastButtonStates) - 1; i++){
        lastButtonStates[i] = readings[i];
    }
}


//evaluation of time difference
int evaluate (long signal, long buttonEvent) {
    difference = signal - buttonEvent; //save time gap between action and reaction
}
