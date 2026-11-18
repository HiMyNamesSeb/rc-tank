/*
  SERVO ONLY test - no typing needed, it moves by itself.
  Wiring: servo orange -> D9, red -> +5V rail, brown -> GND rail,
          Nano GND -> GND rail.
  Expect: Nano's onboard LED blinks each move, servo swings 0 -> 90 -> 180,
          Serial Monitor (9600) prints the angle.
*/
#include <Servo.h>

Servo s;
const int angles[] = {0, 90, 180, 90};

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  s.attach(9);
  Serial.println("Servo test running");
}

void loop() {
  for (int i = 0; i < 4; i++) {
    s.write(angles[i]);
    digitalWrite(LED_BUILTIN, i % 2);
    Serial.print("Servo angle: ");
    Serial.println(angles[i]);
    delay(1000);
  }
}
