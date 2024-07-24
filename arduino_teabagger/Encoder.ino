// display setup 
// https://docs.arduino.cc/learn/electronics/lcd-displays/

#include <LiquidCrystal.h>
#include "rotaryEncoder.h"

#define rs 7
#define en 6
#define d4 5
#define d5 4
#define d6 3
#define d7 2

int globalState = 0;

const char tempText[] = "Temp";
const char timeText[] = "Time left ";
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int maxSec = 5940;
const int maxTemp = 100;
int temp = 100;
int seconds = 0;

unsigned long startTime;

void setup() { 
  Serial.begin(9600);
  // Reads the initial state of the outputA


  lcd.begin(16, 2);
  lcd.print(tempText);
  lcd.setCursor(0, 1);
  lcd.print(timeText);
} 

void loop() {
  if (globalState == 0){ // Select temp
    updateValEncoder(temp, maxTemp, 0, 5);
    printTemp(int(temp));
    confirmSelection(globalState);
  }
  if (globalState == 1){ // Select time
    updateValEncoder(seconds, maxSec, 0, 5);
    printTime(seconds/60, seconds%60);
    confirmSelection(globalState);
    startTime = millis();
  }
  if (globalState == 2){ // Timer countDown
    countdown();
    if(getSecLeft() <= 0){
      globalState++;
    }

  }
}


void temperature(){

  lcd.setCursor(10, 0);

  // Print the time left
  lcd.print(22);

  lcd.setCursor(12, 0);
  lcd.print("C");

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
void printTime(long min, long sec){
  lcd.setCursor(11, 1); 
  if(min < 10){
    lcd.print(0);
  }
  lcd.print(min);
  lcd.print(":");
  if (sec < 10) {
    lcd.print(0);
  }
  lcd.print(sec);
}
void printTemp(int t){
    lcd.setCursor(12, 0);
    if (t < 100){ 
      lcd.print(" ");
    }
    // Print the time left
    lcd.print(t);

    lcd.setCursor(15, 0);
    lcd.print("C");
}