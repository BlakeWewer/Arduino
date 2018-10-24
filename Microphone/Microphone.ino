#define MIC_PIN "A0"
const int sampleWindow = 100; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample = 0;

void setup() 
{
   Serial.begin(9600);
}
 
 
void loop() 
{
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(A0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 5.0) / 1024.0;  // convert to volts
 
  Serial.print(volts);
  Serial.print("  ");
  Serial.print(peakToPeak);
  Serial.print("  ");
  Serial.print(signalMin);
  Serial.print("  ");
  Serial.print(signalMax);
  Serial.print("  ");
  Serial.println(sample);
  peakToPeak = 0;
  volts = 0;
  signalMin = 1024;
  signalMax = 0;
}

