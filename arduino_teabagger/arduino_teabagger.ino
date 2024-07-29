// display setup 
// https://docs.arduino.cc/learn/electronics/lcd-displays/

#include "rotaryEncoder.h"
#include "stepper.h"
#include "lcd.h"
#include "temp.h"

int globalState = 0;

const int maxTemp = 100;
int temp = 100;

const int maxSec = 5940;
int seconds = 0;
unsigned long startTime;

const unsigned int blinkInterval = 500;

void setup() {
  Serial.begin(9600);
  // Reads the initial state of the outputA
  setupRotaryEncoderPins();
  setupLCD();
  setupTemp();
  setupStepperPins();
} 

void loop() {
  switch(globalState){
    case 0:
      clearDisplay();
      printWelcomeTxt();
      delay(2000);
      clearDisplay();
      printLCDText();
      printTime(0,0);
      globalState++;
      break;
    case 1: // Select temp
      updateValEncoder(temp, maxTemp, 0, 5);
      printTemp(int(temp));
      flashTextOn("Temp", 0, 0, blinkInterval);
      confirmSelection(globalState);
      break;
    case 2: // turn off flashing text
      flashTextOff("Temp", 0,0);
      globalState ++;
      break;
    case 3: // Select time
      updateValEncoder(seconds, maxSec, 0, 5);
      printTime(seconds/60, seconds%60);
      flashTextOn("Time", 0, 1, blinkInterval);
      confirmSelection(globalState);
      break;
    case 4: // turn off flashing text
      flashTextOff("Time", 0,1);
      globalState ++;
      break;
    case 5: // wait until temp is correct - TODO
      printTempOfTemp(int(getTemp()), temp);
      startTime = millis();
      if (int(getTemp()) <= temp && !tempIncreasing()) {
        globalState ++;
      }
      confirmSelection(globalState);
      break;
    case 6: // move motor
      moveToPos(POS_BOTTOM);
      globalState ++;
      break;
    case 7: // Timer countDown
      if(getSecLeft() <= 0){
        globalState++;
      }
      printTempOfTemp(int(getTemp()),temp);
      countdown();
      break;
    case 8:
      clearDisplay();
      globalState ++;
      break;
    case 9:
      printTeaBaggerTxt();
      moveToPos(POS_TOP);
      break;
  }
}

void countdown(){
  unsigned long timeLeft = getSecLeft();
  printTime(timeLeft/60, timeLeft%60);

}
long getSecLeft(){
  //Returns the seconds remaining from the timer
  unsigned long timeLeft = seconds > getElapsedSec(startTime) ? seconds - getElapsedSec(startTime) : 0;

  return timeLeft;
}
long getElapsedSec(long time){
  return (millis() - time) / 1000;
}