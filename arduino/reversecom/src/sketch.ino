
#define BUFFER_SIZE 20
#define LED 9

char incomingBuffer[BUFFER_SIZE];
char incoming;
int incomingCounter = 0;

int firstValue, secondValue, thirdValue; // fourthValue, fifthValue, ... // add more if needed
 
void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}
 
void readSerial()
{
  while(Serial.available())
  {
    incoming = Serial.read(); // read single incommning bytes
 
    if(incoming != 'r') //if no carriage return is received proceed in reading the serial port
    {
      incomingBuffer[incomingCounter++] = incoming; // go on the next position in the buffer
    }
    else //read until a carriage ('r') is received
    {
      incomingBuffer[incomingCounter] = '\0'; // set the last byte to NULL to sign it for the string operators
 
      char *a = strtok(incomingBuffer, ",.;"); // split the string after delimiters into tokens
      char *b = strtok(NULL, ",.;"); // ...
      char *c = strtok(NULL, ",.;"); // ...
      //char *d = strtok(NULL, ",.;"); // add another line if needed
 
      firstValue = atoi(a); // convert the strings into integers
      secondValue = atoi(b); // ...
      thirdValue = atoi(c); // ...
      //fourthValue = atoi(d); // add another line if needed    
       
      incomingCounter = 0; // reset the counter
      memset(incomingBuffer, 0, BUFFER_SIZE); //overwrite the incomingBuffer
    }
  }
}
 
void loop()
{
  readSerial(); // read the values available at the serial port
   
  Serial.print(firstValue); // debugging
  Serial.print("t");
  Serial.print(secondValue);
  Serial.print("t");
  Serial.print(thirdValue);
  Serial.print("t");
  //Serial.print(fourthValue); // add these lines if needed
  Serial.println(); // send a carriage return for debugging 

  if(firstValue > 250){
  	digitalWrite(LED, HIGH);
      
  } else {
  	digitalWrite(LED, LOW);
  }

}