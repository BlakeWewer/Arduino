#include <LiquidCrystal.h>

LiquidCrystal LcDriver(11, 9, 5, 6, 7, 8);

String readString;
char c;
int encoderPosition;
enum BStates{ Idle, Wait, Low };
BStates ButtonState;
unsigned long ButtonTime;

/**
 * ButtonNextState
 * @param int Input - either 1 or 0
 * 
 * @return int - always returns 0
 */
int ButtonNextState(int Input)
{
  
  switch(ButtonState)                   //Begins case-switch
  { 
  case Idle:                            //Idle case
    if(Input == LOW)                    //If input is low
    {
      ButtonTime = millis();            //Set ButtonTime to current running time
      ButtonState = Wait;               //Change State to Wait
    }
    break;                              //End of Idle Case
  
  case Wait:
    if(Input == HIGH)
    {
      ButtonState = Idle;
    }
    else if(millis() - ButtonTime >= 5)
    {
      ButtonState = Low;
    return 1;
    }
    break;
  
  case Low:
    if(Input == HIGH)
    {
      ButtonState = Idle;
    }
    break;
  }
  return 0;
}

void MonitorA()
{
  if(digitalRead(2) == digitalRead(3))      //If inputA and inputB are equal
  {
    //encoderPosition--;      //Decrement encoderPosition  
    LcDriver.scrollDisplayLeft(); 
  }
  else
  {
    //encoderPosition++;      //Else, increment encoderPosition
    //LcDriver.scrollDisplayRight();
  }
}

void MonitorB()
{
  if(digitalRead(2) == digitalRead(3))      //If inputA and inputB are equal
  {
    //encoderPosition++;      //Increment encoderPosition  
    LcDriver.scrollDisplayRight();  
  }
  else
  {
    //encoderPosition--;      //Else, decrement encoderPosition
    //LcDriver.scrollDisplayLeft();
  }
}

void setup()
{
  LcDriver.begin(16, 2);
  LcDriver.leftToRight();
  LcDriver.clear();
  LcDriver.setCursor(0, 0);               //Set up the LcDriver and put cursor at 0, 0
  pinMode(4, INPUT);
  ButtonState = Idle;                      //Set timer to the current millis
  attachInterrupt(0, MonitorA, CHANGE);   //Set MonitorA() to interrupt 0
  attachInterrupt(1, MonitorB, CHANGE);   //Set MonitorB() to interrupt 1
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

  if (readString.length() > 0)
  {
    LcDriver.clear();
    LcDriver.setCursor(0, 0);
    for (int i = readString.length() - 1; i >= 0; i--)
    {
      Serial.write(readString[i]);
      LcDriver.print(readString[i]);
    }
    readString = "";
    Serial.println();
  } // end if
}
