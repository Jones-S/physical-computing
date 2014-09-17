#include <Arduino.h>

void setup();
void loop();
void startFade(int led);
#line 1 "src/sketch.ino"
/*
 Fade

 This example shows how to fade an LED on pin 9
 using the analogWrite() function.

 This example code is in the public domain.
 */

int led1 = 11;           // the pin that the LED is attached to
int led2 = 10;           // the pin that the LED is attached to
int led3 = 6;           // the pin that the LED is attached to

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int active_led = 0;
long interval = 600;
long previousMillis = 0;

// the setup routine runs once when you press reset:
void setup()
{
    // declare pin 9 to be an output:
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);

}

// the loop routine runs over and over again forever:
void loop()
{
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis > interval)
    {
        startFade(active_led);

        if (active_led == 2)
        {
            active_led = 0;
        }
        else
        {
            active_led++;
        }
    }




}

void startFade(int led)
{

    // reverse the direction of the fading at the ends of the fade:
    for (int i = 0; i < 256; i++)
    {
        // set the brightness of pin:
        analogWrite(led1, brightness);
        // change the brightness for next time through the loop:
        brightness = brightness + fadeAmount;

        if (brightness == 0 || brightness == 255)
        {
            fadeAmount = -fadeAmount;
        }
    }

}