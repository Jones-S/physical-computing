#define INPUT_COIL A1
#define INPUT_BUT1 3
#define INPUT_BUT2 5
#define LED 9

int lastSignal = 0; //will hold the time in ms when the last signal happened
int lastButton = 0; //will hold the time in ms when the button was pressed
int timeBetween = 0;
int inputCoil = 0;

boolean buttonState = false;


void setup(){
  //start serial connection
  Serial.begin(9600);
  pinMode(INPUT_COIL, INPUT);
  pinMode(INPUT_BUT1, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

}

void loop(){
  inputCoil = analogRead(INPUT_COIL);
  buttonState = digitalRead(INPUT_BUT1);
  // Serial.println(inputCoil);
  Serial.println(buttonState);

  if(inputCoil > 300){
  	lastSignal = millis();
  	Serial.print(inputCoil);
  	Serial.print(" ################################");
  	Serial.println();
  }

  if(buttonState){
  	lastButton = millis();
  }

  if(lastSignal && lastButton && lastButton > lastSignal){
  	timeBetween = lastButton - lastSignal;
  	Serial.println(timeBetween);
  }

  digitalWrite(LED, buttonState);


}
