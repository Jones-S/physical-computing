import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.serial.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class sensorinput extends PApplet {


String[] singleValues = new String[2];
int firstValue = 0;
int secondValue = 0;

public void setup() {
	//println(Serial.list());
	Serial arduino = new Serial(this, "/dev/tty.usbmodemfd131", 9600); //initiate serial port with arduino


}

public void draw() {
	background(255);    // Setting the background to white
	stroke(0);          // Setting the outline (stroke) to black
	fill(150);          // Setting the interior of a shape (fill) to grey 
	rect(50,firstValue,75,100); // Drawing the rectangle
	rect(20, 20, 40, 10);

}

public void serialEvent(Serial port){
	if(port.available() > 0){
		String totalString = port.readStringUntil(10); //read until new line (ln)
		if (totalString != null) {
			singleValues = split(totalString, ","); //split strings where commas are
			firstValue = PApplet.parseInt(singleValues[0]);
			secondValue = PApplet.parseInt(singleValues[1]);
		}

	}
}
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "--full-screen", "--bgcolor=#666666", "--stop-color=#cccccc", "sensorinput" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
