#define POT_PIN A1

void setup() {
  Serial.begin(9600); // Set up serial communication with the computer
}
 
void loop() {
  int analogValue = analogRead(POT_PIN);  // Read the input on analog pin 1
  Serial.println(analogValue);       // Print value to serial monitor
  delay(1);                          // Don't do analogRead too often
}
