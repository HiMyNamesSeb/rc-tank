# Phase 0: Separate control experiments

**Status:** ✅ Done

## What
My very first sketches for this project, written by me before Claude got involved in the code. A joystick module controls the SG90 servo and the 28BYJ-48 stepper motor on an Arduino. I wrote two versions:

- **[tankV1](tankV1/tankV1.ino):** uses the built-in `Stepper` library.
- **[tankV2](tankV2/tankV2.ino):** switches to the `AccelStepper` library to get speed control.

## Why
Before designing anything I needed to know I could make each motor move at all, and understand how the joystick readings, the `Servo` library and the stepper libraries work.

## Goal
Joystick Y axis sets the servo angle. Joystick X axis spins the stepper one way or the other.

## Parts used in this phase
- Arduino board `(already have in kit)`
- SG90 servo `(already have in kit)`
- 28BYJ-48 stepper + ULN2003 driver board `(already have in kit)`
- Joystick module `(already have in kit)`, prototyping only
- Breadboard and jumper wires `(already have in kit)`, prototyping only

## Wiring

| From | To |
|---|---|
| Joystick VRx | A0 (stepper) |
| Joystick VRy | A5 (servo) |
| Servo signal (orange) | D3 |
| ULN2003 IN1, IN2, IN3, IN4 | D8, D9, D10, D11 |
| Servo, joystick, ULN2003 power | 5V and GND |

The stepper is created with pins in the order `8, 10, 9, 11` (IN1, IN3, IN2, IN4). That order is what makes the 28BYJ-48 turn instead of just buzzing.

## How each version works

### tankV1 (`Stepper` library)
- Reads the joystick Y axis, maps `0-1023` to `0-180°`, writes it to the servo.
- Reads the joystick X axis, maps it to `-5..5` steps, and steps the motor if it's outside a small dead zone.

### tankV2 (`AccelStepper` library)
- Same servo control.
- Joystick X now sets a **speed** from `-200` to `200` steps/sec, and `runSpeed()` moves the stepper.

## What I learned
- `Stepper.step()` **blocks**: the Arduino can't do anything else until the steps are done, so the servo and stepper can't really move at the same time.
- In V2, `runSpeed()` only takes at most one step each time it's called, and the `delay(30)` in the loop means it only gets called about 33 times a second. So the stepper can never go faster than about 33 steps/sec, no matter where the joystick is.
- Both of these pointed to the fix in Phase 1: write the loop so it never waits, and only move each motor when it's time to.

## Notes from the bench
- I almost short circuited everything a few times, but learning about potentiometers, buttons and the joystick was a good learning experience. The joystick was a lot more responsive to my movements.

## Blog days
- [Day 1 - Proof of concept](https://github.com/HiMyNamesSeb/Blogs/blob/main/rc-tank-project/d1-proof-of-concept.md)
