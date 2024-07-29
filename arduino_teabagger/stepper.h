#ifndef _stepper_h
#define _stepper_h

#define STEPPER_STEP_PIN 10
#define STEPPER_DIR_PIN 9

void setupStepperPins();

const unsigned int POS_TOP = 1;
const unsigned int POS_BOTTOM = 2;

void moveToPos(unsigned int newPos);

#endif