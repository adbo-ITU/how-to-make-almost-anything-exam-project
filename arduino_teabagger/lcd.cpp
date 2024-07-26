#include <Arduino.h>
#include <LiquidCrystal.h>
#include "lcd.h"

const unsigned int LCDWidth = 16;
const unsigned int LCDHeight = 2;

const char tempText[] = "Temp";
const char timeText[] = "Time";
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

unsigned long blinkTime;
const unsigned int blinkInterval = 500;
bool blinkOn = true;

void setupLCD(){
  // set's up the starting LCD size
  lcd.begin(LCDWidth, LCDHeight);
  blinkTime = millis();
}

void printLCDText(){
  // prints the time and temp text
  lcd.setCursor(0, 0);
  lcd.print(tempText);
  lcd.setCursor(0, 1);
  lcd.print(timeText);  
}

void printTime(long min, long sec){
  // Prints the given time on an LCD scren
  lcd.setCursor(11, 1); 
  if(min < 10){ lcd.print(0); }
  lcd.print(min);
  lcd.print(":");
  if (sec < 10) { lcd.print(0); }
  lcd.print(sec);
}

void printTemp(int t){
  // prints the given temperature on an LCD screen
  lcd.setCursor(12, 0);
  if (t < 100){ 
    lcd.print(" ");
  }
  lcd.print(t);

  lcd.setCursor(15, 0);
  lcd.print("C");
}

void flashText(char text[], int locationX, int locationY){
    if (millis() - blinkTime < blinkInterval) {
        return;
    }
    lcd.setCursor(locationX,locationY);
    if (!blinkOn) { // if the text is currently not showing.
        lcd.print(text);
        blinkOn = true;
        blinkTime = millis();
        return;
    }
    int len = sizeof(text) / sizeof(char);
    for (int i = 0; i < len; i++) {
        lcd.print(" ");
    }
    blinkTime = millis();
}