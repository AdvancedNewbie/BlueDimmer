/* Arduino serial test code for controlling the AC Dimmer Board via PWM */

// For testing the AC Dimmer Board upload this sketch to an arduino, open the
// Serial Monitor (9600 baud), and send values (try values 30 to 100 first).  You can testing
// the limits of the range of dimming by starting at around 30 and backing off until 
// 'AC LOAD' is almost zero volts (ie.  25, 23, 21, 19, 18, 17, 16, 15....)
// The same can be done with the maximum.  (ie. 70, 75, 80, 85, 86, 87, 88, 89...)

const int analogOutPin = 9; // Analog output pin that the AC Dimmer Board is connected to
          //   (Digital Pin 9)

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 baud:
  Serial.begin(9600); 
}

void loop() {

  analogWrite(analogOutPin, outputValue);           
  if (stringComplete) {
    Serial.print("Dimmer set to: ");
    Serial.print(inputString);
    Serial.println("%");
    outputValue = inputString.toInt();
    if (outputValue == 0){
      outputValue = 1; 
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    if (inChar != '\n') {
      inputString += inChar;
    }
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}
