#include <math.h>

int led = 10;           // the pin that the LED is attached to
int fadeAmount = 1;    // how many points to fade the LED by
int fadeAmount2 = 1;
int durationOn = 100;
int durationOff = 100;
int roundedOn;
int roundedOff;

void setup()  { 
  pinMode(led, OUTPUT);

} 

// the loop routine runs over and over again forever:
void loop()  { 
  digitalWrite(led, HIGH);
  roundedOn = round(durationOn);
  delay(roundedOn/100);
  digitalWrite(led, LOW);
  roundedOff = round(durationOff);
  delay(roundedOff/100);

  durationOn = durationOn + fadeAmount;
  durationOff = durationOff - fadeAmount2;


  if (durationOn == 0 || durationOn == 600) {
    fadeAmount = -fadeAmount ; 
  } else if (durationOff == 0 || durationOff == 600){
    fadeAmount2 = -fadeAmount2;
  }    
}