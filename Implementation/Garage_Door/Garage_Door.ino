#include <Stepper.h>

#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)

Stepper stepper(STEPS, 8, 10, 9, 11);

void setup() {
  // nothing to do
}

void loop() {
  // Changing direction to clockwise
  stepper.setSpeed(14); // 1 rpm
  stepper.step(2038); // do 2038 steps -- corresponds to one revolution in one minute
  delay(50); // wait for one second
  stepper.setSpeed(14); // 1 rpm
  stepper.step(2038);// do 2038 steps -- corresponds to one revolution in one minute
  delay(50);
  stepper.setSpeed(14); // 1 rpm
  stepper.step(1038); // do 2038 steps -- corresponds to one revolution in one minute
//  delay(50); // wait for one second
//  stepper.setSpeed(14); // 1 rpm
//  stepper.step(1019);
  
  
  delay(2000); // wait for one second
  
  // change direction to anticlockwise
  stepper.setSpeed(14); // 6 rpm
  stepper.step(-2038);
  delay(50);// do 2038 steps in the other direction with faster speed -- corresponds to one revolution in 10 seconds
  stepper.setSpeed(14); // 6 rpm
  stepper.step(-2038);
  delay(50);
  stepper.setSpeed(14); // 6 rpm
  stepper.step(-1038);
//  delay(50);// do 2038 steps in the other direction with faster speed -- corresponds to one revolution in 10 seconds
//  stepper.setSpeed(14); // 6 rpm
//  stepper.step(-1019);
  delay(2000);
}
