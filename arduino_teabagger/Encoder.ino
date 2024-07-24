// display setup 
// https://docs.arduino.cc/learn/electronics/lcd-displays/

#include <LiquidCrystal.h>

#define rotaryPinA 11
#define rotaryPinB 12
#define rotaryButtonpin 13

#define rs 7
#define en 6
#define d4 5
#define d5 4
#define d6 3
#define d7 2

const int maxSec = 5940;
const int maxTemp = 100;
int temp;
int seconds;
unsigned long startTime;

int aState;
int aLastState;
bool encoderButtonState;
bool encoderButtonLastState;
int globalState;

char tempText[] = "Temp";
char timeText[] = "Time left ";
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() { 
  // set rotary pins
  pinMode(rotaryPinA, INPUT);
  pinMode(rotaryPinB, INPUT);
  pinMode(rotaryButtonpin, INPUT);
   
  Serial.begin(9600);
  // Reads the initial state of the outputA
  aLastState = digitalRead(rotaryPinA);
  encoderButtonLastState = digitalRead(rotaryButtonpin);
  globalState = 0;
  temp = 100;
  seconds = 0;

  lcd.begin(16, 2);
  lcd.print(tempText);
  lcd.setCursor(0, 1);
  lcd.print(timeText);
} 

void loop() {
  if (globalState == 0){ // Select temp
    updateValEncoder(temp, maxTemp, 0, 5);
    printTemp(int(temp));
    confirmSelection();
  }
  if (globalState == 1){ // Select time
    updateValEncoder(seconds, maxSec, 0, 5);
    printTime(seconds/60, seconds%60);
    confirmSelection();
    startTime = millis();
  }
  if (globalState == 2){ // Timer countDown
    countdown();
    if(getSecLeft() <= 0){
      globalState++;
    }

  }
}

void updateValEncoder(int &val, int maxval, int minval, int interval){
    aState = digitalRead(rotaryPinA); // Reads the "current" state of the outputA
    // If the previous and the current state of the outputA are different, that means a Pulse has occured
    if (aState != aLastState){     
      // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
      if (digitalRead(rotaryPinB) != aState) { 
        if(val > minval) {val -=interval;} // 
      } else {
        if(val < maxval) {val +=interval;} // 
      }
      Serial.print("value: ");
      Serial.println(val);
    } 
    aLastState = aState; // Updates the previous state of the outputA with the current state
}
void confirmSelection(){
  encoderButtonState = digitalRead(rotaryButtonpin);
  if (encoderButtonState !=encoderButtonLastState) {
    if (encoderButtonState == 0) {
      Serial.println("Button was pressed");
      globalState ++;
      Serial.println(globalState);
    }
    encoderButtonLastState = encoderButtonState;
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
