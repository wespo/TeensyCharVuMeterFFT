#define SDI 11
#define CLK 13
#define LE 9
#define OE 8

#include "Arduino.h"

//Bit Mapping to pins on LED driver
  //1 = LOW 4
  //2 = MID 4
  //3 = HIGH 4
  //4 = LOW 3
  //5 = MID 3
  //6 = HIGH 3
  //7 = NONE
  //8 = NONE
  //9 = NONE
  //10 = NONE
  //11 = HIGH 2
  //12 = MED 2
  //13 = LOW 2
  //14 = LOW 1
  //15 = MED 1
  //16 = HIGH 1
#define HIGH_MASK 0x3009 //hardware specific pin mapping for LEDs. See above table
#define MID_MASK 0x4812
#define LOW_MASK 0x8424

void initLED();
void writeOne(int digit);
void bargraph(byte low, byte mid, byte high, bool dotbar);
int convertColsToBits(byte colVal, bool dotbar);


