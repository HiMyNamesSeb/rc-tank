#include <AccelStepper.h>
#include <Servo.h>

// Stepper setup: type 4 = 4 wire (ULN2003)
AccelStepper myStepper(AccelStepper::FULL4WIRE, 8, 10, 9, 11);

// Servo setup
Servo myServo;
int servoPin = 3;

// Joystick pins
int potPinX = A0; // stepper speed
int potPinY = A5; // servo control

void setup() {
  myServo.attach(servoPin);

  myStepper.setMaxSpeed(1000);     // max speed in steps/sec
}

void loop() {
  // --- Servo control ---
  int Yreading = analogRead(potPinY);
  int angle = map(Yreading, 0, 1023, 0, 180);
  myServo.write(angle);
  delay(30);

  // --- Stepper speed control ---
  int Xreading = analogRead(potPinX);
  int speed = map(Xreading, 0, 1023, -200, 200); // speed in steps/sec
  myStepper.setSpeed(speed);
  myStepper.runSpeed(); // non-blocking movement
}
