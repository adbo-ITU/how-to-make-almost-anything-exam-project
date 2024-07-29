#include "rotaryEncoder.h"
#include <Arduino.h>

int aState;
int aLastState = digitalRead(rotaryPinA);
bool encoderButtonState;
bool encoderButtonLastState = digitalRead(rotaryButtonpin);


void setupRotaryEncoderPins(){
  // set rotary pins
  pinMode(rotaryPinA, INPUT);
  pinMode(rotaryPinB, INPUT);
  pinMode(rotaryButtonpin, INPUT);
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
    } 
    aLastState = aState; // Updates the previous state of the outputA with the current state
}
void confirmSelection(int &state){
  //When a button is pressed and released a state is increased.
  encoderButtonState = digitalRead(rotaryButtonpin);
  if (encoderButtonState !=encoderButtonLastState) {
    if (encoderButtonState == 0) {
      state ++;
    }
    encoderButtonLastState = encoderButtonState;
  }
}