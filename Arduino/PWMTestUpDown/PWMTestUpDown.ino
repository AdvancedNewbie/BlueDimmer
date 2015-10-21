/* Arduino smooth dimming code for controlling the AC Dimmer Board via PWM */

const int analogOutPin = 9; // Analog output pin that the AC Dimmer Board is connected to
			                      //   (Digital Pin 9)
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
//pinMode(analogOutPin, OUTPUT);
  // initialize serial communications at 9600 baud:
  Serial.begin(9600); 
}

void loop() {

while (outputValue < 100){
  delay(10);
  analogWrite(analogOutPin, outputValue);
  sendSerialMessage();
  outputValue++;
}

while (outputValue > 1){
  delay(10);
  analogWrite(analogOutPin, outputValue);
  sendSerialMessage();
  outputValue--;
}

}

void sendSerialMessage(){
    Serial.print("Dimmer set to: ");
    Serial.print(outputValue);
    Serial.println("%");
}

