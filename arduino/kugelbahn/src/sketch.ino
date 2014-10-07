#define INPUT_PIN A1
#define LED 9

void setup(){
  //start serial connection
  Serial.begin(9600);
  pinMode(INPUT_PIN, INPUT);
  pinMode(LED, OUTPUT);

}

void loop(){
  //read the pushbutton value into a variable
  int inputSignal = analogRead(INPUT_PIN);
  //print out the value of the pushbutton
  Serial.println(inputSignal);
  if(inputSignal > 300){
  	digitalWrite(LED, HIGH);
  	// delay(1000);
  	Serial.print(inputSignal);
  	Serial.print(" ################################");
  	Serial.println();

  } else {
  	digitalWrite(LED, LOW);
  }

}
