// DmxSimple Library: http://code.google.com/p/tinkerit/
// RS-232 code adapted from https://www.arduino.cc/en/Tutorial/ArduinoSoftwareRS232

#include <ctype.h>
#include "showDef.h"
#include <DmxSimple.h>

//List of fixture addresses and number of channels to turn off for clearAll()
int fixtureList[2][7] = {{ 2, 7, 20, 47, 51, 72, 100},
                         { 3, 4, 3,  4,  4,  4,  4  }};

#define bit2400Delay 416
#define halfBit2400Delay 208
#define RS_232_TX 3

#define SHOW_SIGNAL1 9
#define SHOW_SIGNAL2 8
#define SHOW_SIGNAL3 7

byte tx = 3;
byte SWval;
byte running = 1;

int currentShowStep = 0;
unsigned long showTimer = 0;
int showStarted = 0;
unsigned long nextStepTime = 0;
int timerSet = 0;
int count = 0;

void setup()
{
  Serial.begin(115200);
  DmxSimple.usePin(5);
  DmxSimple.maxChannel(4);

  //Turn the sign on
  DmxSimple.write(31, 255);

  //Turn on the Button and button sign
  DmxSimple.write(90, 255);
  
  pinMode(tx, OUTPUT);
  digitalWrite(tx, HIGH);
  delay(2);

  //Serial.println("Ready to start");
  
}

void loop()
{

  //setTimer();
  if(digitalRead(SHOW_SIGNAL2) == HIGH)
  {
    if(timerSet == 0)
    {
      //Serial.println("Setting Timer");
      setTimer();
      timerSet = 1;
    }
  }
  if(digitalRead(SHOW_SIGNAL3) == HIGH)
  {
    // Run the show
    if(!showStarted)
    {
      //Serial.println("Starting Show");
      //Turn off the Button and button sign
      DmxSimple.write(90, 0);
      showStarted = 1;
      showTimer = millis();
    }
    else
    {
      nextStepTime = (startTime[currentShowStep]);
      nextStepTime = nextStepTime * 100;

      /*count += 1;
      if(count == 10000)
      {
      //Serial.print("Current Step: ");
      //Serial.print(currentShowStep);
      //Serial.print(" Next Step Time: ");
      //Serial.print(nextStepTime);
      //Serial.print(" Current Time: ");
      //Serial.println(millis() - showTimer);
      count = 0;
      };*/
      
      if(millis() - showTimer >= (nextStepTime))
      {
        //Serial.print("Fixture: ");
        //Serial.print(fixtureNumber[currentShowStep]);
        //Serial.print(" Value: ");
        Serial.println(sendValue[currentShowStep]);
        DmxSimple.write(fixtureNumber[currentShowStep], sendValue[currentShowStep]);
        if(currentShowStep < NUM_DEF)
        {
          currentShowStep += 1;
        };
      }
    }
    
  }
  else
  {
    //Stop the show
    if(showStarted)
    {
      //Turn on the Button and button sign
      DmxSimple.write(90, 255);
      showStarted = 0;
      clearAll();
      timerSet = 0;
      //Serial.println("Show Stopped");
      currentShowStep = 0;
    };
  }
}
//

// Send data to RS-232 bus
void SWprint(int data)
{
  byte mask;
  //startbit
  digitalWrite(tx,LOW);
  delayMicroseconds(bit2400Delay);
  for (mask = 0x01; mask>0; mask <<= 1) {
    if (data & mask){ // choose bit
     digitalWrite(tx,HIGH); // send 1
    }
    else{
     digitalWrite(tx,LOW); // send 0
    }
    delayMicroseconds(bit2400Delay);
  }
  //stop bit
  digitalWrite(tx, HIGH);
  delayMicroseconds(bit2400Delay);
}

//Set up the countdown timer
void setTimer()
{
  /*// Settings found at: http://www.ats-usa.com/pdf_manuals/354man3.pdf
  
  //Serial.println("Enter setting timer");
  
  SWprint(0x11); // Initialize
  
  SWprint(0x00); // Address
  
  SWprint(0x05); // Mode Setting
  
  SWprint(0x00); // Digit 0 (Leave 0)
  SWprint(0x00); // Digit 1 (Leave 0)
  SWprint(0x00); // Digit 2
  SWprint(0x00); // Digit 3
  SWprint(0x01); // Digit 4
  SWprint(0x07); // Digit 6
  
  SWprint(0x02); // Misc Settings
  */
}

// Blanks out all lights except the sign.
void clearAll()
{
  for(int f = 0; f <= 6; f++)
  {
    int startAddress = fixtureList[0][f];
    int endAddress = fixtureList[0][f] + fixtureList[1][f];
    for(int n = startAddress; n < endAddress; n++)
    {
         DmxSimple.write(n, 0);
    }
  }
}
