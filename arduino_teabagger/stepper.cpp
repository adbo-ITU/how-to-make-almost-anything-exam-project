#include "stepper.h"
#include <Arduino.h>

void setupStepperPins() {
  pinMode(STEPPER_STEP_PIN, OUTPUT);
  pinMode(STEPPER_DIR_PIN, OUTPUT);
}

// Do NOT modify this variable directly. Use `moveToPos()`, which controls it
// internally.
unsigned int curPos = POS_TOP;

// Do not use this function directly. Use user-friendly wrapper `moveToPos()`.
// If you use this function yourself, you may violate some assumptions.
void rotateStepper(unsigned int dir, unsigned int revolutions) {
  const unsigned int STEPPER_SPEED = 700;
  const unsigned int STEPPER_STEP_CYCLES_PER_REV = 200;

  unsigned int iters = revolutions * STEPPER_STEP_CYCLES_PER_REV;

  digitalWrite(STEPPER_DIR_PIN, dir);
  for (int x = 0; x < iters; x++) {
    digitalWrite(STEPPER_STEP_PIN, HIGH);
    delayMicroseconds(STEPPER_SPEED);
    digitalWrite(STEPPER_STEP_PIN, LOW);
    delayMicroseconds(STEPPER_SPEED);
  }
}

void moveToPos(unsigned int newPos) {
  // Sanity check - maybe we fuck up, but that shouldn't break the mechanics
  if (newPos != POS_TOP && newPos != POS_BOTTOM)
    return;

  if (newPos == curPos)
    return;

  unsigned int direction = newPos == POS_TOP ? LOW : HIGH;
  const unsigned int REVS_FROM_TOP_TO_BOTTOM = 4;

  rotateStepper(direction, REVS_FROM_TOP_TO_BOTTOM);
  curPos = newPos;
}
