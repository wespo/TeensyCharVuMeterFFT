#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "bargraph.h"



// GUItool: begin automatically generated code
AudioInputAnalog         adc1(A0);           //xy=402,333
AudioAnalyzeFFT1024      fft1024_1;      //xy=574,327
AudioConnection          patchCord1(adc1, fft1024_1);
// GUItool: end automatically generated code


const int BeatLed = 5;           // the pin that the LED is attached to
const int HatLed = 6;           // the pin that the LED is attached to
void setup()
{
  // Audio requires memory to work.
  AudioMemory(60);

  pinMode(BeatLed, OUTPUT);
  pinMode(HatLed, OUTPUT);
 initLED();
 Serial.begin(115200);
}

#define NUM_BANDS 5
float bands[NUM_BANDS] = {0};
int bandbins[NUM_BANDS][2] = {{0,2},
                      {2,5},
                      {5,10},
                      {11,50},
                      {80,260}};

float decay[NUM_BANDS] = {0.6,0.99,0.98,0.97,0.4};

void drawBands(float* vals, bool dotBar)
{
  int beat = int(constrain(round(200000 * vals[0]),0,255));
  int low = int(constrain(round(vals[1]*4+1),0,4));
  int mid = int(constrain(round(vals[2]*4+1),0,4));
  int high = int(constrain(round(vals[3]*3+1),0,4));
  int hat = int(constrain(round(100 * vals[4]),0,70));
  bargraph(low, mid, high, true);
  analogWrite(BeatLed, beat);    
  analogWrite(HatLed, hat);    
}
void loop()
{

  if(fft1024_1.available())
  {
    for(int i = 0; i < NUM_BANDS; i++)
    {
      float newVal = log(10*fft1024_1.read(bandbins[i][0],bandbins[i][1]))/2.3;
      if(newVal > bands[i])
      {
        bands[i] = newVal;
      }
      else
      {
        bands[i] = bands[i] * decay[i];
      }
    }
        
    drawBands(bands,true);
  }
}

