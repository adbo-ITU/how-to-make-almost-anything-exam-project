#define stepPin 10
#define dirPin 11

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
  vroom(HIGH, 2);
  delay(1000);

  vroom(LOW, 4);
  delay(1000);
}

void vroom(unsigned int dir, unsigned int revolutions) {
  const unsigned int STEPPER_SPEED = 700;
  const unsigned int STEPPER_STEP_CYCLES_PER_REV = 200;

  unsigned int iters = revolutions * STEPPER_STEP_CYCLES_PER_REV;

  digitalWrite(dirPin, dir);
  for (int x = 0; x < iters; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(STEPPER_SPEED);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(STEPPER_SPEED);
  }
}
