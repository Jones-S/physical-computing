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

public class reversecom extends PApplet {


Serial myPort;

public void setup() {
	background(0);
	size(512, 512);
	println(Serial.list());
	myPort = new Serial(this, "/dev/tty.usbmodemfd131", 9600);
}

public void draw() {
	int firstValue = mouseX;
	int secondValue = 222;
	int thirdValue = 333;

	myPort.write(str(firstValue));
	myPort.write(",");
	myPort.write(str(secondValue));
	myPort.write(",");
	myPort.write(str(thirdValue));
	myPort.write(",");
	myPort.write("r"); 
	delay(200);
	
}
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "--full-screen", "--bgcolor=#666666", "--stop-color=#cccccc", "reversecom" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
