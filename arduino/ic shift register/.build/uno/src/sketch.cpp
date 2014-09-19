#include <Arduino.h>

void setup();
void loop();
#line 1 "src/sketch.ino"
#define LATCH_PIN 8  //Pin zu ST_CP vom 74HC595
#define CLOCK_PIN 12 //Pin zu SH_CP vom 74HC595
#define DATA_PIN 11  //Pin zu DS vom 74HC595
 
void setup() 
{
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
}
 
void loop() 
{
  for (int numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) 
  {
    digitalWrite(LATCH_PIN, LOW);  // LATCH_PIN auf LOW = Beginn der Daten
 
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, numberToDisplay); // Daten shiften
 
    digitalWrite(LATCH_PIN, HIGH);  // LATCH_PIN auf HIGH = LEDs leuchten
 
    delay(300);
  }
}
