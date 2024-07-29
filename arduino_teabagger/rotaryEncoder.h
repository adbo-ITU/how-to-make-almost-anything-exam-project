#ifndef _rotaryEncoder_h
#define _rotaryEncoder_h

#define rotaryPinA 11
#define rotaryPinB 12
#define rotaryButtonpin 13

void setupRotaryEncoderPins();
void updateValEncoder(int &val, int maxval, int minval, int interval);
void confirmSelection(int &globalState);

#endif