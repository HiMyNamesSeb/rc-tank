/*
  RC Tank - barrel + turret breadboard test
  Board: Arduino Nano (ATmega328P)

  SG90 servo            = barrel ELEVATION (up/down)
  28BYJ-48 + ULN2003    = TURRET ROTATION (left/right)

  Uses only built-in libraries (Servo, Stepper) - nothing to install.

  Both motors run at the same time: the loop never blocks, it just
  nudges the servo one degree or the stepper one step when it's time.

  Serial Monitor: 9600 baud, line ending = "Newline". Type ? for help.
*/

#include <Servo.h>
#include <Stepper.h>

// ---------------- Pins ----------------
const uint8_t SERVO_PIN = 9;     // servo orange (signal) wire
const uint8_t IN1 = 4;           // ULN2003 IN1
const uint8_t IN2 = 5;           // ULN2003 IN2
const uint8_t IN3 = 6;           // ULN2003 IN3
const uint8_t IN4 = 7;           // ULN2003 IN4

// ---------------- Servo (elevation) settings ----------------
const int ELEV_MIN     = 10;    // lowest angle allowed. Narrow these once the
const int ELEV_MAX     = 170;   // barrel is mounted so it can't hit anything.
const int ELEV_START   = 90;    // angle at power-up
const int ELEV_NUDGE   = 5;     // degrees moved by 'u' / 'd'
const unsigned long ELEV_MS_PER_DEG = 15;  // bigger = slower, smoother barrel

// ---------------- Stepper (turret) settings ----------------
const int  STEPS_PER_REV = 2048;   // 28BYJ-48 in full-step mode (output shaft)
const int  TURRET_RPM    = 12;     // 10-15 is reliable for this motor at 5 V
const bool RELEASE_WHEN_IDLE = true; // turn coils off when stopped (stays cool;
                                     // set false if the turret must hold firmly)

// IMPORTANT: the 28BYJ-48 needs pins in the order IN1, IN3, IN2, IN4
// with the Stepper library, otherwise it just buzzes or jitters.
Stepper turret(STEPS_PER_REV, IN1, IN3, IN2, IN4);
Servo   barrel;

// ---------------- State ----------------
int  elevNow    = ELEV_START;   // where the servo is right now
int  elevTarget = ELEV_START;   // where we want it
unsigned long lastElevMove = 0;

long turretPos    = 0;          // steps from "zero"
long turretTarget = 0;
unsigned long lastStepUs = 0;
const unsigned long STEP_INTERVAL_US = 60000000UL / ((unsigned long)STEPS_PER_REV * TURRET_RPM);
bool coilsOn = false;

char cmdBuf[24];
uint8_t cmdLen = 0;

// ---------------- Motor helpers ----------------
// To swap roles later, these four functions are the only things to change.
void setElevation(int angle) {
  elevTarget = constrain(angle, ELEV_MIN, ELEV_MAX);
}

void moveTurretSteps(long steps) {
  turretTarget += steps;
}

void moveTurretDegrees(long deg) {
  moveTurretSteps(deg * STEPS_PER_REV / 360);
}

void releaseCoils() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  coilsOn = false;
}

// Called every loop: moves the servo 1 degree toward its target when it's time.
void updateServo() {
  if (elevNow == elevTarget) return;
  if (millis() - lastElevMove < ELEV_MS_PER_DEG) return;
  lastElevMove = millis();
  elevNow += (elevTarget > elevNow) ? 1 : -1;
  barrel.write(elevNow);
}

// Called every loop: takes 1 stepper step toward its target when it's time.
void updateStepper() {
  if (turretPos == turretTarget) {
    if (RELEASE_WHEN_IDLE && coilsOn) releaseCoils();
    return;
  }
  if (micros() - lastStepUs < STEP_INTERVAL_US) return;
  lastStepUs = micros();
  int dir = (turretTarget > turretPos) ? 1 : -1;
  turret.step(dir);     // returns right away because we already waited
  turretPos += dir;
  coilsOn = true;
}

// ---------------- Serial commands ----------------
void printHelp() {
  Serial.println(F("--- Barrel/turret test commands ---"));
  Serial.println(F("e<angle>  set elevation, e.g. e120"));
  Serial.println(F("u / d     elevation up / down by 5 deg"));
  Serial.println(F("t<deg>    turn turret by degrees, e.g. t90 or t-45"));
  Serial.println(F("s<steps>  turn turret by raw steps (2048 = 1 turn)"));
  Serial.println(F("h         turret back to zero"));
  Serial.println(F("z         call current turret position zero"));
  Serial.println(F("x         stop turret now"));
  Serial.println(F("demo      move both motors at once"));
  Serial.println(F("?         this help + status"));
}

void printStatus() {
  Serial.print(F("Elevation: "));
  Serial.print(elevNow);
  Serial.print(F(" -> "));
  Serial.print(elevTarget);
  Serial.print(F(" deg   Turret: "));
  Serial.print(turretPos);
  Serial.print(F(" -> "));
  Serial.print(turretTarget);
  Serial.print(F(" steps ("));
  Serial.print(turretPos * 360L / STEPS_PER_REV);
  Serial.println(F(" deg)"));
}

void handleCommand(char *cmd) {
  if (cmd[0] == '\0') return;
  long value = atol(cmd + 1);

  if (strcmp(cmd, "demo") == 0) {
    setElevation(elevNow > 90 ? ELEV_MIN + 20 : ELEV_MAX - 20);
    moveTurretDegrees(180);
    Serial.println(F("Demo: servo and stepper moving together"));
    return;
  }

  switch (cmd[0]) {
    case 'e': case 'E': setElevation(value); break;
    case 'u': case 'U': setElevation(elevTarget + ELEV_NUDGE); break;
    case 'd': case 'D': setElevation(elevTarget - ELEV_NUDGE); break;
    case 't': case 'T': moveTurretDegrees(value); break;
    case 's': case 'S': moveTurretSteps(value); break;
    case 'h': case 'H': turretTarget = 0; break;
    case 'z': case 'Z': turretPos = turretTarget = 0; break;
    case 'x': case 'X': turretTarget = turretPos; break;
    case '?': printHelp(); break;
    default:
      Serial.print(F("Unknown command: "));
      Serial.println(cmd);
      return;
  }
  printStatus();
}

void readSerial() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      cmdBuf[cmdLen] = '\0';
      handleCommand(cmdBuf);
      cmdLen = 0;
    } else if (cmdLen < sizeof(cmdBuf) - 1 && c != ' ') {
      cmdBuf[cmdLen++] = c;
    }
  }
}

// ---------------- Setup / loop ----------------
void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  releaseCoils();

  turret.setSpeed(TURRET_RPM);

  barrel.write(ELEV_START);   // set the angle BEFORE attach so it doesn't jump
  barrel.attach(SERVO_PIN);

  Serial.println(F("RC tank barrel test ready."));
  printHelp();
  printStatus();
}

void loop() {
  readSerial();
  updateServo();
  updateStepper();
}
