#define INPUT_INDUCTOR A1
#define INPUT_BUT1 2
#define INPUT_BUT2 3
#define LED 9
#define CLOCK 5
#define LATCH 6
#define DATA 7

const int arraySize = 2;

int inputInductor = 0;
int readings[2];
int highestPeak = 0;                    // save the highest peak in the period when the sphere passes the inductor

boolean buttonStates[2];                // actual current button state without flickering
boolean newButtonChange[2];             // flags for buttonEvents

boolean lastButtonStates[2] = {LOW, LOW};      // buttonStates from last loop
boolean newSignal = false;
boolean secondNewSignal = false;            // register if 2 signals have passed, in case both players had a failure
int minTimeBeforeCoil = 700;            // minTimeBeforeCoil in ms, you can't click in this time range otherwise it'll result in a fail

//booleans for saving fails
boolean fails[2] = {false, false};              // failure states in array


// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTimes[2] = {0, 0};     // the last time the input button 2 was toggled
int debounceDelay = 50;                 // the debounce time; increase if the output flickers
int minInterspace = 500;                // minimum Time between the inductors -> reset highestPeak

long lastButtonSignals[2] = {0, 0};
long lastSignal = 0;                    // var for saving time of last inductor signal
int timeDifference = 0;                 // var for saving the difference in time between newSignal and lastButtonSignal

boolean points[2][6];                   // array with points, 2x for each player and 6 points possible:
int pointsPosCounter = 0;              // array with current position of points array, can go until max points (at this time 6)

void setup() {
    //start serial connection
    Serial.begin(9600);
    pinMode(INPUT_INDUCTOR, INPUT);
    pinMode(INPUT_BUT1, INPUT_PULLUP);  //PULLUP Resistor activated -> Signal reverted button off = 1;
    pinMode(INPUT_BUT2, INPUT_PULLUP);
    pinMode(LED, OUTPUT);
    pinMode(LATCH, OUTPUT);
    pinMode(CLOCK, OUTPUT);
    pinMode(DATA, OUTPUT);
    //reset Score to 0 for both players
    resetScore();
    // Serial.println();
    printShift();


}

void loop() {
    //TODO:
    //avoid points if button is pressed during the increasing of the copper signals
    //TODO2:
    //set 0 if both players have failed (2nd signal etc.)

    //read analog input (0 - 1023) from copper inductor
    inputInductor = analogRead(INPUT_INDUCTOR);
    // if(inputInductor > 4){
    //  Serial.println(inputInductor);
    // }

    if (inputInductor > 20 && inputInductor > highestPeak) {
        // check if last Signal was a long time ago, if so set 2ndSignal flag
        if (millis() - lastSignal > minInterspace && newSignal) {
            secondNewSignal = true;
            Serial.println("2ND Signal!");
            //after 2 players failed and no evaluation can take place and a 2nd signal came -> reset fails of both players
            resetFails();
        }
        highestPeak = inputInductor; //save new highest value
        lastSignal = millis();
        newSignal = true;
        Serial.print("______^__ NEW PEAK: "); Serial.println(lastSignal);
    }
    // if a certain time has passed highest Peak will be reset
    if (millis() - lastSignal > minInterspace && lastSignal != 0) {
        highestPeak = 0;
        // Serial.println("----------- Reset");
    }

    // read the state of the switch into a local variable:
    readings[0] = !digitalRead(INPUT_BUT1); //reverse value because of pullup resistor: 0 if button is pressed
    readings[1] = !digitalRead(INPUT_BUT2); //reverse value because of pullup resistor: 0 if button is pressed

    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH),  and you've waited
    // long enough since the last press to ignore any noise:

    for (int i = 0; i < arraySize; i++) {
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
                //set new ButtonSignal flag
                newButtonChange[i] = true;
            }

            //check if button is HIGH && if button is newly changed -> save time to lastButtonSignal
            if (buttonStates[i] == HIGH && newButtonChange[i]) {
                lastButtonSignals[i] = millis();
                Serial.print("Last Time Button Pressed : "); Serial.print(lastButtonSignals[i]); Serial.print(" of Player Nr.: "); Serial.print(i); Serial.println();
                //reset ButtonEventFlag
                newButtonChange[i] = false;
            }
        }

        //check if somebody has clicked too early and only if somebody clicked (otherwise it would be executed from the beginning)
        //also exclude normal buttonEvents which would evaluate below 0 > TRUE: <minTimeBeforeCoil
        //only do it if fail is still true
        int timeToSignal = lastSignal - lastButtonSignals[i];
        if ( 0 < timeToSignal && timeToSignal < minTimeBeforeCoil && lastButtonSignals[i] != 0 && !fails[i]) {
            //set failure for the player releasing too early
            fails[i] = true;
            Serial.println("BIG FAIL");
        }

        //check if evaluation is necessary
        //only check if newSignal, button was pressed after a newSignal and there has not been a failure
        if (newSignal && lastButtonSignals[i] > 0 && lastButtonSignals[i] - lastSignal > 0 && !fails[i]) {
            evaluate (lastButtonSignals[i], lastSignal, i); //pass TimeEvents and Player (0 or 1)
        }
    }




    // save the reading.  Next time through the loop,
    // it'll be the lastButtonState:
    for (int i = 0; i < arraySize; i++) {
        lastButtonStates[i] = readings[i];
    }

    //if one or both buttonStates are On LED lights up
    if (buttonStates[0] || buttonStates [1]) {
        digitalWrite(LED, HIGH);
    } else {
        digitalWrite(LED, LOW);
    }

    printShift();
}


//evaluation of time difference
int evaluate (long buttonEvent, long signal, int player) {
    //save time gap between action and reaction
    timeDifference =  buttonEvent - signal;
    Serial.println(); Serial.print(timeDifference); Serial.print(" = Reaction Delay from Player: "); Serial.print(player);
    Serial.print(" – last Button: "); Serial.print(lastButtonSignals[player]); Serial.print(" – and last Signal: "); Serial.println(lastSignal);
    // reset newSignal flag so that further evaluation is impossible
    newSignal = false;
    secondNewSignal = false;
    if (player == 0){
    	points[0][pointsPosCounter] = 1; //set a point (1) at the current pos in the players score (points)
    	points[1][pointsPosCounter] = 0; //set a 0 for the other player at the same position in the score
    } else if(player == 1){
    	points[1][pointsPosCounter] = 1;
    	points[0][pointsPosCounter] = 0;
    }
    pointsPosCounter += 1; //increase current position in counter array by 1.
    //if somebody scored reset fails of both players
    for(int i=0; i< 6; i++){
        Serial.print(points[player][i]); Serial.print(", ");
    }
    Serial.println();
    resetFails();
}

void resetScore() {
    //fill points array with 0
    for (int i = 0; i < sizeof(points); i++) {
        for (int j = 0; j < sizeof(points) - 1; j++) {
            points[i][j] = 0;
        }
    }
}

void resetFails() {
    for (int i = 0; i < 2; i++) {
        fails[i] = false;
    }
}

void printShift() {

	byte myByte =  170; //64 in binary = 0100 0000

    // Serial.println(myByte, BIN);

    digitalWrite(LATCH, LOW);

    shiftOut(DATA, CLOCK, LSBFIRST, myByte);

    digitalWrite(LATCH, HIGH);

}
