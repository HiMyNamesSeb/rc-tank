#include <Stepper.h>
#define STEPS_PER_REV 2048
Stepper myStepper(STEPS_PER_REV, 8, 10, 9, 11); // correct pin order for ULN2003

#include <Servo.h>
Servo myServo;

int servoPin = 3;
int potPinX = A0;
int potPinY = A5;

void setup() {
  myStepper.setSpeed(10); // start slow
  myServo.attach(servoPin);
}

void loop() {
  int Yreading = analogRead(potPinY);
  int angle = map(Yreading, 0, 1023, 0, 180);
  myServo.write(angle);

  delay(15);
  
  int Xreading = analogRead(potPinX);
  int mapped = map(Xreading, 0, 1023, -5, 5);

  if (abs(mapped) > 1) {
    myStepper.step(mapped);
  }
}
