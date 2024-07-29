#include "stepper.h"

void setup1() {
  setupStepperPins();
}

void loop1() {
  moveToPos(POS_BOTTOM);
  delay(1000);

  moveToPos(POS_TOP);
  delay(1000);
}