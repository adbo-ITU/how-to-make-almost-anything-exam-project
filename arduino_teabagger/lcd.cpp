#include <Arduino.h>
#include <LiquidCrystal.h>
#include "lcd.h"

const unsigned int LCDWidth = 16;
const unsigned int LCDHeight = 2;

const char tempText[] = "Temp";
const char timeText[] = "Time";
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

unsigned long blinkTime;
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

void flashTextOn(char text[], int locationX, int locationY, int time){
    // flashes the 
    // Note remember to turn flashText off, by using the function.
    if (millis() - blinkTime < time) {
        return;
    }
    lcd.setCursor(locationX,locationY);
    if (!blinkOn) { // if the text is currently not showing.
        lcd.print(text);
        blinkOn = true;
        blinkTime = millis();
        return;
    }

    for (int i = 0; i < strlen(text); i++) {
        lcd.print(" ");
    }
    blinkTime = millis();
    blinkOn = false;
}

void flashTextOff(char text[], int locationX, int locationY){
    //
    blinkOn = true;
    lcd.setCursor(locationX,locationY);
    lcd.print(text);
}

void clearDisplay(){
    for (int i = 0; i < LCDHeight; i++) {
        lcd.setCursor(0, i);
        for (int j = 0; j < LCDWidth; j++) {
            lcd.print(" ");
        }
    }
}

void printTeaBaggerTxt(){
    // Prints a goodbye message
    lcd.setCursor(2,0);
    lcd.print("Your tea has");
    lcd.setCursor(1,1);
    lcd.print("been teabagged");
}

void printWelcomeTxt(){
    // Prints a goodbye message
    lcd.setCursor(3,0);
    lcd.print("Welcome to");
    lcd.setCursor(1,1);
    lcd.print("The Teabagger");
}