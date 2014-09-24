import processing.serial.*;
String[] singleValues = new String[2];
int firstValue = 0;
int secondValue = 0;

void setup() {
	//println(Serial.list());
	Serial arduino = new Serial(this, "/dev/tty.usbmodemfd131", 9600); //initiate serial port with arduino


}

void draw() {
	background(255);    // Setting the background to white
	stroke(0);          // Setting the outline (stroke) to black
	fill(150);          // Setting the interior of a shape (fill) to grey 
	rect(50,firstValue,75,100); // Drawing the rectangle
	rect(20, 20, 40, 10);

}

void serialEvent(Serial port){
	if(port.available() > 0){
		String totalString = port.readStringUntil(10); //read until new line (ln)
		if (totalString != null) {
			singleValues = split(totalString, ","); //split strings where commas are
			firstValue = int(singleValues[0]);
			secondValue = int(singleValues[1]);
		}

	}
}