// display setup 
// https://docs.arduino.cc/learn/electronics/lcd-displays/

#include "rotaryEncoder.h"
#include "lcd.h"

int globalState = 0;

const int maxTemp = 100;
int temp = 100;

const int maxSec = 5940;
int seconds = 0;
unsigned long startTime;


void setup() { 
  Serial.begin(9600);
  // Reads the initial state of the outputA
  setupRotaryEncoderPins();
  setupLCD();
  printLCDText();
} 

void loop() {
  if (globalState == 0){ // Select temp
    updateValEncoder(temp, maxTemp, 0, 5);
    printTemp(int(temp));
    flashTextOn("Temp", 0,0);
    confirmSelection(globalState);
  }
  if (globalState == 1){
    flashTextOff("Temp", 0,0);
    globalState ++;
  }
  if (globalState == 2){ // Select time
    updateValEncoder(seconds, maxSec, 0, 5);
    printTime(seconds/60, seconds%60);
    flashTextOn("Time", 0,1);
    confirmSelection(globalState);
    startTime = millis();
  }
  if (globalState == 3){
    flashTextOff("Time", 0,1);
    globalState ++;
  }
  if (globalState == 4){ // Timer countDown
    if(getSecLeft() <= 0){
      globalState++;
    }
    countdown();
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