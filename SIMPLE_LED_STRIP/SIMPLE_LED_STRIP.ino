// Christmas Color Changer for 2 Analog LED Strips
// 12/2012 Carl F Sutter
// with thanks to Adafruit!

// 2 LED strips with RED, GREEN, BLUE LEDS on each, so there are 6 channels to control via FET transistors
// use the 6 PWM digital I/O pins for the FET gate pins
#define RED1 5
#define GREEN1 3
#define BLUE1 9
/*   #define RED2 9
   #define GREEN2 10
   #define BLUE2 11
*/
#define FADESPEED 7 // make this higher to slow down

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;


void setup() {
  // set all the LEDs to off
  analogWrite(RED1, 0);
  analogWrite(GREEN1, 0);
  analogWrite(BLUE1, 0);
  /*      analogWrite(RED2, 0);
        analogWrite(GREEN2, 0);
        analogWrite(BLUE2, 0);
  */
  Serial.begin(9600);
}

void loop() {
  
    unsigned long startMillis = millis(); // Start of sample window
    unsigned int peakToPeak = 0; // peak-to-peak level
    unsigned int signalMax = 0;
    unsigned int signalMin = 1024;
    // collect data for 50 mS
    while (millis() - startMillis < sampleWindow)
    {
      sample = analogRead(0);
      if (sample < 1024) // toss out spurious readings
      {
        if (sample > signalMax)
        {
          signalMax = sample; // save just the max levels
        }
        else if (sample < signalMin) {
          signalMin = sample; // save just the min levels
        }
      }
    }
    peakToPeak = signalMax - signalMin; // max - min = peak-peak amplitude
    double volts = (peakToPeak * 5.0) / 1024; // convert to volts
    Serial.println(volts);
    /*

          int i;

          // fade strip 1 red up and strip 2 red up
          for (i = 0; i < 256; i++) {
            analogWrite(RED1, i);
      //        analogWrite(RED2, i);
            delay(FADESPEED);
          }

          // fade strip 1 red down and strip 2 red down
          for (i = 0; i < 256; i++) {
            analogWrite(RED1, 255-i);
      //      analogWrite(RED2, 255-i);
            delay(FADESPEED);
          }

          // fade strip 1 green up and strip 2 green up
          for (i = 0; i < 256; i++) {
            analogWrite(GREEN1, i);
      //       analogWrite(GREEN2, i);
            delay(FADESPEED);
          }

          // fade strip 1 green down and strip 2 green down
          for (i = 0; i < 256; i++) {
            analogWrite(GREEN1, 255-i);
      //       analogWrite(GREEN2, 255-i);
            delay(FADESPEED);
          }

          // fade both strips blue up
          for (i = 0; i < 256; i++) {
            analogWrite(BLUE1, i);
      //       analogWrite(BLUE2, i);
            delay(FADESPEED);
          }

          // fade both strips blue down
          for (i = 0; i < 256; i++) {
            analogWrite(BLUE1, 255-i);
      //        analogWrite(BLUE2, 255-i);
            delay(FADESPEED);
          }

          // fade both strips red and green up
          for (i = 0; i < 256; i++) {
            analogWrite(RED1, i);
            analogWrite(GREEN1, i);
      //       analogWrite(RED2, i);
      //       analogWrite(GREEN2, i);
            delay(FADESPEED);
          }

          // fade both strips red and green down
          for (i = 0; i < 256; i++) {
            analogWrite(RED1, 255-i);
            analogWrite(GREEN1, 255-i);
      //        analogWrite(RED2, 255-i);
      //       analogWrite(GREEN2, 255-i);
            delay(FADESPEED);
          }

          // fade strip 1 red up and strip 2 green up
          for (i = 0; i < 256; i++) {
            analogWrite(RED1, i);
      //        analogWrite(GREEN2, i);
            delay(FADESPEED);
          }

          // fade strip 1 red down and strip 2 green down
          for (i = 0; i < 256; i++) {
            analogWrite(RED1, 255-i);
      //       analogWrite(GREEN2, 255-i);
            delay(FADESPEED);
          }

          // fade strip 2 red up and strip 1 green up
          for (i = 0; i < 256; i++) {
            analogWrite(GREEN1, i);
      //      analogWrite(RED2, i);
            delay(FADESPEED);
          }

          // fade strip 2 red down and strip 1 green down
          for (i = 0; i < 256; i++) {
            analogWrite(GREEN1, 255-i);
      //       analogWrite(RED2, 255-i);
            delay(FADESPEED);
          }
    */
  }

