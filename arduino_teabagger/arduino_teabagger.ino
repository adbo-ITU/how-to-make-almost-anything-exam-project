#include "stepper.h"

void setup() {
  setupStepperPins();
}

void loop() {
  moveToPos(POS_BOTTOM);
  delay(1000);

  moveToPos(POS_TOP);
  delay(1000);
}
