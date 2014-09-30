#include <Servo.h>
#define INPUT_PIN 5
Servo myservo;

int inputVal = 0;
 
void setup()
{
  myservo.attach(9);
  myservo.write(0);
  Serial.begin(9600);
}
 
void loop()
{
  inputVal = analogRead(INPUT_PIN);
  //map inputVal to degree
  int mappedVal = map(inputVal, 0, 1023, 0, 180);


  myservo.write(mappedVal);
  delay(1000);

  Serial.println(inputVal);
  
}