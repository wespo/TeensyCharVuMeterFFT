#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "bargraph.h"



// GUItool: begin automatically generated code
AudioInputAnalog         adc1(A0);           //xy=402,333
AudioFilterStateVariable filter2;        //xy=609,335
AudioFilterStateVariable filter3;        //xy=613,406
AudioFilterStateVariable filter1;        //xy=616,258
AudioAnalyzePeak         peak1;          //xy=807,233
AudioAnalyzePeak         peak2;          //xy=832,280
AudioAnalyzePeak         peak5;          //xy=833,425
AudioAnalyzePeak         peak3;          //xy=846,322
AudioAnalyzePeak         peak4;          //xy=852,378
AudioConnection          patchCord1(adc1, 0, filter1, 0);
AudioConnection          patchCord2(adc1, 0, filter2, 0);
AudioConnection          patchCord3(adc1, 0, filter3, 0);
AudioConnection          patchCord4(filter2, 1, peak3, 0);
AudioConnection          patchCord5(filter3, 1, peak4, 0);
AudioConnection          patchCord6(filter3, 2, peak5, 0);
AudioConnection          patchCord7(filter1, 0, peak1, 0);
AudioConnection          patchCord8(filter1, 1, peak2, 0);
// GUItool: end automatically generated code

const int BeatLed = 5;           // the pin that the LED is attached to
const int HatLed = 6;           // the pin that the LED is attached to
void setup()
{
  // Audio requires memory to work.
  AudioMemory(12);

  //set up filters
  filter1.frequency(100);
  filter2.frequency(200);
  filter3.frequency(400);

  pinMode(BeatLed, OUTPUT);
  pinMode(HatLed, OUTPUT);

 initLED();
}


void loop()
{
  int beat = int(round(255 * peak1.read()));
  int low = int(round(peak2.read()*3+1));
  int mid = int(round(peak3.read()*3+1));
  int high = int(round(peak4.read()*3+1));
  int hat = int(round(255 * peak5.read()));
  bargraph(low, mid, high, true);
  analogWrite(BeatLed, beat);    
  analogWrite(HatLed, hat);    
  delay(20);
}

