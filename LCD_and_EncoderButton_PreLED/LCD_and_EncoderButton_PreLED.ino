#include <LinkedList.h>
#include <LiquidCrystal.h>



LiquidCrystal LcDriver(11, 9, 5, 6, 7, 8);
LinkedList<String*> myMenu = LinkedList<String*>();
String m0 = "Strobe";
String m1 = "KSU";
String m2 = "USA";
unsigned long Timer;
double encoderPosition;
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
    if(encoderPosition < myMenu.size()-1)
      encoderPosition+=.25;      //Increment encoderPosition     
  }
  else
  {
    if(encoderPosition > 0)
      encoderPosition-=.25;      //Else, decrement encoderPosition
  }
}

void MonitorB()
{
  if(digitalRead(2) == digitalRead(3))      //If inputA and inputB are equal
  {
    if(encoderPosition > 0)
      encoderPosition-=.25;      //Decrement encoderPosition    
  }
  else
  {
    if(encoderPosition < myMenu.size()-1)
      encoderPosition+=.25;      //Else, increment encoderPosition
  }
}

void setup()
{
  LcDriver.begin(16, 2);
  LcDriver.clear();
  LcDriver.setCursor(0, 0);               //Set up the LcDriver and put cursor at 0, 0
  pinMode(4, INPUT);
  ButtonState = Idle;
  Timer = millis();                       //Set timer to the current millis
  attachInterrupt(0, MonitorA, CHANGE);   //Set MonitorA() to interrupt 0
  attachInterrupt(1, MonitorB, CHANGE);   //Set MonitorB() to interrupt 1

  myMenu.add(&m0);
  myMenu.add(&m1);
  myMenu.add(&m2);
}

void loop()
{
  if(millis() - Timer > 100)              //Every 100 milliseconds
  {
    LcDriver.clear();
    LcDriver.setCursor(0, 0);
    LcDriver.print((int)encoderPosition);      //Clear and Print the encoderPosition to the LcDriver
    LcDriver.setCursor(0, 1);
    LcDriver.print(*myMenu.get((int)encoderPosition));
    Timer +=100;                          //Increase Timer by 100
  }
  if(ButtonNextState(digitalRead(4)))     //If Button Pressed
  {
    LcDriver.clear();    
    LcDriver.setCursor(0, 0);
    encoderPosition = 0;
    LcDriver.print((int)encoderPosition);
    
  }
}
