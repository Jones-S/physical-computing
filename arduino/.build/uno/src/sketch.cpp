#include <Arduino.h>

void setup();
void loop();
#line 1 "src/sketch.ino"
int led = 10;           // the pin that the LED is attached to
int fadeAmount = 5;    // how many points to fade the LED by
int duration = 10;

void setup()  { 
  pinMode(led, OUTPUT);

} 

// the loop routine runs over and over again forever:
void loop()  { 
  digitalWrite(led, HIGH);
  delay(duration); 

  duration = duration + fadeAmount;

  if (duration == 0 || duration == 1000) {
    fadeAmount = -fadeAmount ; 
  }     
}