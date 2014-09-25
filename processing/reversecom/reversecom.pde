import processing.serial.*;
Serial myPort;

void setup() {
	background(0);
	size(512, 512);
	println(Serial.list());
	myPort = new Serial(this, "/dev/tty.usbmodemfd131", 9600);
}

void draw() {
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