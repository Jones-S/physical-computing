#define DEVICE A1
int inputInductorDevice = 0;

void setup() {
    //start serial connection
    Serial.begin(9600);
    pinMode(DEVICE, INPUT);
}    


void loop() {
    //read analog input (0 - 1023) from copper inductor
    inputInductorDevice = analogRead(DEVICE);

   

    //TODO: check highest peak signal

        Serial.print(inputInductorDevice);
        Serial.print(" ################################");
        Serial.println();
    }

