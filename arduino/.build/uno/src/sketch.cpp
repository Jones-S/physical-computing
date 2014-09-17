#include <Arduino.h>

void setup();
void loop();
#line 1 "src/sketch.ino"
// /*
//   Shift Register Example
//  for 74HC595 shift register

//  This sketch turns reads serial input and uses it to set the pins
//  of a 74HC595 shift register.

//  Hardware:
//  * 74HC595 shift register attached to pins 2, 3, and 4 of the Arduino,
//  as detailed below.
//  * LEDs attached to each of the outputs of the shift register

//  Created 22 May 2009
//  Created 23 Mar 2010
//  by Tom Igoe

//  */

// //Pin connected to latch pin (ST_CP) of 74HC595
// const int latchPin = 8;
// //Pin connected to clock pin (SH_CP) of 74HC595
// const int clockPin = 12;
// ////Pin connected to Data in (DS) of 74HC595
// const int dataPin = 11;

// void setup() {
//   //set pins to output because they are addressed in the main loop
//   pinMode(latchPin, OUTPUT);
//   pinMode(dataPin, OUTPUT);
//   pinMode(clockPin, OUTPUT);
//   Serial.begin(9600);
//   Serial.println("reset");
// }

// void loop() {
//   if (Serial.available() > 0) {
//     // ASCII '0' through '9' characters are
//     // represented by the values 48 through 57.
//     // so if the user types a number from 0 through 9 in ASCII,
//     // you can subtract 48 to get the actual value:
//     int bitToSet = Serial.read() - 48;

//   // write to the shift register with the correct bit set high:
//     registerWrite(bitToSet, HIGH);
//   }
// }

// // This method sends bits to the shift register:

// void registerWrite(int whichPin, int whichState) {
// // the bits you want to send
//   byte bitsToSend = 0;

//   // turn off the output so the pins don't light up
//   // while you're shifting bits:
//   digitalWrite(latchPin, LOW);

//   // turn on the next highest bit in bitsToSend:
//   bitWrite(bitsToSend, whichPin, whichState);

//   // shift the bits out:
//   shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);

//     // turn on the output so the LEDs can light up:
//   digitalWrite(latchPin, HIGH);

// }

//**************************************************************//
//  Name    : shiftOutCode, Hello World
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis
//  Date    : 25 Oct, 2006
//  Modified: 23 Mar 2010
//  Version : 2.0
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255
//****************************************************************

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

int led = 5;



void setup()
{
    Serial.begin(9600);
    //set pins to output so you can control the shift register
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(led, OUTPUT);


}

void loop()
{
    digitalWrite(latchPin, LOW);
    digitalWrite(clockPin, LOW); //set it to low again
    
    digitalWrite(dataPin, LOW);
    digitalWrite(clockPin, HIGH); //into storage
    digitalWrite(latchPin, HIGH); //shift into real life
    delay(500);

    //count from 0 to 255 and display the number
    // on the LEDs


    // for (int numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++)
    // {
    //     // take the latchPin low so
    //     // the LEDs don't change while you're sending in bits:
    //     digitalWrite(latchPin, LOW);
    //     // shift out the bits:
    //     shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);

    //     //take the latch pin high so the LEDs will light up:
    //     digitalWrite(latchPin, HIGH);
    //     // pause before next value:
    //     delay(500);
    //     digitalWrite(led, HIGH);
    //     delay(400);
    //     digitalWrite(led, LOW);

    //     Serial.println(numberToDisplay);


    // }



    // for (int i = 0; i < 20; i++)
    // {
    //     if (i == 0)
    //     {
    //         digitalWrite(dataPin, LOW);
    //         digitalWrite(clockPin, HIGH); //into storage
    //         digitalWrite(clockPin, LOW); //set it to low again
    //         digitalWrite(latchPin, HIGH); //shift into real life
    //         digitalWrite(latchPin, LOW);
    //         delay(500);
    //     } else if (i > 0 & i < 3) {
    //      digitalWrite(dataPin, HIGH);
    //         digitalWrite(clockPin, HIGH); //into storage
    //         digitalWrite(clockPin, LOW); //set it to low again
    //         digitalWrite(dataPin, LOW);
    //         digitalWrite(latchPin, HIGH); //shift into real life
    //         digitalWrite(latchPin, LOW);
    //         delay(500);
    //     } else if ( i > 2 ){
    //      digitalWrite(dataPin, LOW);
    //         digitalWrite(clockPin, HIGH); //into storage
    //         digitalWrite(clockPin, LOW); //set it to low again
    //         digitalWrite(latchPin, HIGH); //shift into real life
    //         digitalWrite(latchPin, LOW);
    //         delay(500);
    //     } else {
    //      digitalWrite(led, HIGH);
    //      delay(100);
    //      digitalWrite(led, LOW);
    //     }
    // }

}


// /* -----------------------------------------------------------------------------------
//  Fade

//  This example shows how to fade an LED on pin 9
//  using the analogWrite() function.

//  This example code is in the public domain.
//  */

// int led = 9;           // the pin that the LED is attached to
// int brightness = 0;    // how bright the LED is
// int fadeAmount = 5;    // how many points to fade the LED by

// // the setup routine runs once when you press reset:
// void setup()
// {
//     // declare pin 9 to be an output:
//     pinMode(led, OUTPUT);
// }

// // the loop routine runs over and over again forever:
// void loop()
// {
//     // set the brightness of pin 9:
//     analogWrite(led, brightness);

//     // change the brightness for next time through the loop:
//     brightness = brightness + fadeAmount;

//     // reverse the direction of the fading at the ends of the fade:
//     if (brightness == 0 || brightness == 255)
//     {
//         fadeAmount = -fadeAmount ;
//     }
//     // wait for 30 milliseconds to see the dimming effect
//     delay(30);

// }