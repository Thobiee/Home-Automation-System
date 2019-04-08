#include <Stepper.h>

#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)

Stepper stepper(STEPS, 8, 10, 9, 11);

void setup() {
  // nothing to do
}

void loop() {
  // Changing direction to clockwise
  stepper.setSpeed(14); // 1 rpm
  stepper.step(510); // do 2038 steps -- corresponds to one revolution in one minute
  
  
  delay(2000); // wait for one second
  
  // change direction to anticlockwise
  stepper.setSpeed(14); // 6 rpm
  stepper.step(-510);
  
  delay(2000);
}
