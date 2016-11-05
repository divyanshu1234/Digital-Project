#include <SevSeg.h>



SevSeg sevseg;

void setup()
{
  byte numDigits = 4;   
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13}; //Segments: A,B,C,D,E,F,G,Period

  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(10);
}

void loop()
{
  static byte decPlace = 0;
  
  sevseg.setNumber(8888,decPlace);
  decPlace++;
  decPlace %= 4; 

  sevseg.refreshDisplay(); 
}

