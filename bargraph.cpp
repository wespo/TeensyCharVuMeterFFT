#include "bargraph.h"

void initLED()
{
  //port initialization
  pinMode(SDI,OUTPUT);
  digitalWrite(SDI,LOW);
  pinMode(CLK,OUTPUT);
  digitalWrite(CLK,LOW);
  pinMode(LE,OUTPUT);
  digitalWrite(LE,LOW);
  pinMode(OE, OUTPUT);
  digitalWrite(OE, LOW);
}

//display functions
void writeOne(int digit)
{

  //print digit
  for(int i = 0; i < 16; i++)
  {
    byte toggle = (digit >> i) & 0x01 ;
    //data
    digitalWrite(SDI,toggle);
    //shift
    digitalWrite(CLK,HIGH);
    digitalWrite(CLK,LOW);
  }
  digitalWrite(LE,HIGH);
  digitalWrite(LE,LOW);

}

void bargraph(byte low, byte mid, byte high, bool dotbar)
{
  low %= 5;
  mid %= 5;
  high %= 5;
  unsigned int bitstream = (convertColsToBits(low, dotbar) & LOW_MASK) 
                         | (convertColsToBits(mid, dotbar) & MID_MASK) 
                         | (convertColsToBits(high, dotbar) & HIGH_MASK);
  writeOne(bitstream); 
}

int convertColsToBits(byte colVal, bool dotbar)
{
  unsigned int posmask = 0xFFFF;
  colVal = (4-colVal)*3; //groups of 3 leds
  
  if(colVal >= 6) //special case to handle wired gap in board.
  {
    colVal +=4;
  }
  if(dotbar) //dot mode (mask out lower values)
  {
    if(colVal < 12) //because of wired gap in board
    {
      posmask = (posmask << colVal) & (~(posmask << (colVal + 3)));
    }
    else
    {
      posmask <<= colVal;
    }
    
  }
  else //bar
  {
    posmask <<= colVal;
  }
  
  return posmask;
}
