/*
  STEPPER ONLY test - no library, no typing needed.
  Wiring: D4 -> IN1, D5 -> IN2, D6 -> IN3, D7 -> IN4,
          ULN2003 + -> +5V rail, - -> GND rail, Nano GND -> GND rail,
          motor plugged into the white socket.
  Expect:
    1) SLOW part: the 4 LEDs (A B C D) on the ULN2003 light one after
       another, 1 per second. The shaft barely moves - that's normal.
    2) FAST part: the shaft turns about 1 full turn one way, then back.
  Serial Monitor (9600) says which part is running.
*/
const int pins[4] = {4, 5, 6, 7};

void setCoil(int n) {            // energize one coil (0-3)
  for (int i = 0; i < 4; i++) digitalWrite(pins[i], i == n ? HIGH : LOW);
}

void allOff() {
  for (int i = 0; i < 4; i++) digitalWrite(pins[i], LOW);
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) pinMode(pins[i], OUTPUT);
  allOff();
}

void loop() {
  Serial.println("SLOW: watch LEDs A, B, C, D light in order");
  for (int n = 0; n < 4; n++) {
    Serial.print("  IN");
    Serial.println(n + 1);
    setCoil(n);
    delay(1000);
  }

  Serial.println("FAST: one turn forward");
  for (int s = 0; s < 2048; s++) { setCoil(s % 4); delay(3); }

  Serial.println("FAST: one turn back");
  for (int s = 2047; s >= 0; s--) { setCoil(s % 4); delay(3); }

  allOff();
  delay(1000);
}
