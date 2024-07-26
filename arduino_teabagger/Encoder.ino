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

const unsigned int blinkInterval = 500;

void setup() { 
  Serial.begin(9600);
  // Reads the initial state of the outputA
  setupRotaryEncoderPins();
  setupLCD();
  printWelcomeTxt();
} 

void loop() {
  if (globalState == 0){
    clearDisplay();
    printWelcomeTxt();
    delay(2000);
    clearDisplay();
    printLCDText();

    globalState++;
  }
  if (globalState == 1){ // Select temp
    updateValEncoder(temp, maxTemp, 0, 5);
    printTemp(int(temp));
    flashTextOn("Temp", 0, 0, blinkInterval);
    confirmSelection(globalState);
  }
  if (globalState == 2){
    flashTextOff("Temp", 0,0);
    globalState ++;
  }
  if (globalState == 3){ // Select time
    updateValEncoder(seconds, maxSec, 0, 5);
    printTime(seconds/60, seconds%60);
    flashTextOn("Time", 0, 1, blinkInterval);
    confirmSelection(globalState);
    startTime = millis();
  }
  if (globalState == 4){
    flashTextOff("Time", 0,1);
    globalState ++;
  }
  if (globalState == 5){ // Timer countDown
    if(getSecLeft() <= 0){
      globalState++;
    }
    countdown();
  }
  if (globalState == 6) {
    clearDisplay();
    globalState ++;
  }
  if (globalState == 7) {
    printTeaBaggerTxt();
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