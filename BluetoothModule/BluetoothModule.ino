String readString;
char c;
void setup()
{
 Serial.begin(9600);
 Serial.println("OK then, you first, say something.....");
 Serial.println("Go on, type something and hit Send,");
 Serial.println("or just hit the Enter key,");
 Serial.println("then I will repeat it!");
 Serial.println("");
}
void loop() {
 while (Serial.available())
 {
 delay(3);
 c = Serial.read();
 readString += c;
 }// end while
 if (readString.length() >0)
 {
  for(int i = 0; i < readString.length(); i++)
  {
    Serial.write(readString[i]);
  }
 readString="";
 Serial.println();
 } // end if
}
