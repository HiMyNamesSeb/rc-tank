# RC Tank

📓 **Daily build blog:** [Blogs / rc-tank-project](https://github.com/HiMyNamesSeb/Blogs/tree/main/rc-tank-project)

## What I'm building and why

I'm building a remote-controlled tank from scratch: tread drive, a turret that rotates left and right, and a barrel that tilts up and down, all controlled wirelessly from my phone over Bluetooth.

This is my first real electronics project. I want to actually understand how the pieces work (motors, drivers, power, microcontrollers) instead of just buying something that already works, and I want a project I can work on day by day and look back on. It starts on a breadboard with my starter kit, then moves to drive motors and wireless control, and ends with a custom PCB and a finished tank.

> **Disclaimer:** All of the building, wiring, testing and debugging in this project is my own work. I'm learning as I go from online electrical engineering tutorials, and I use Claude (an AI assistant) to help with formatting and presenting this repo and blog.

## Parts checklist (finished tank only)

Parts used only for prototyping and testing are listed in each phase's folder, not here.

Status key: `(already have in kit)` · `(salvaged)` · `(bought)` · `(not bought yet)`

**Brains and control**
- [ ] ESP32-WROOM-32 dev board (Bluetooth control) `(not bought yet)`

**Turret and barrel**
- [x] SG90 micro servo, barrel elevation `(already have in kit)`
- [x] 28BYJ-48 stepper motor, turret rotation `(already have in kit)`
- [x] ULN2003 stepper driver board `(already have in kit)`

**Drive**
- [ ] Tank tread chassis with 2 DC gear motors `(not bought yet)`
- [ ] TB6612FNG dual motor driver `(not bought yet)`

**Power**
- [ ] 2S 7.4V LiPo battery (or 6×AA holder) `(not bought yet)`
- [ ] LiPo balance charger (only if using LiPo) `(not bought yet)`
- [ ] 5V buck converter, LM2596 or MP1584 (powers servo, stepper and logic) `(not bought yet)`
- [ ] Main power switch `(not bought yet)`
- [x] 100µF electrolytic capacitor (smooths servo power) `(already have in kit)`

**Board and wiring**
- [ ] Custom PCB (designed in Phase 5) `(not bought yet)`
- [x] Jumper wires / Dupont cables `(already have in kit)`

## Phases

| # | Phase | Status |
|---|---|---|
| 0 | [Separate control experiments](phase-0-separate-control/) | ✅ Done |
| 1 | [Proof of concept: barrel + turret demo](phase-1-proof-of-concept/) | ✅ Done |
| 2 | [Drive and treads](phase-2-drive-treads/) | ⏳ Not started |
| 3 | [Wireless control (ESP32 Bluetooth)](phase-3-wireless-control/) | ⏳ Not started |
| 4 | [Chassis integration](phase-4-chassis-integration/) | ⏳ Not started |
| 5 | [Custom PCB](phase-5-custom-pcb/) | ⏳ Not started |
| 6 | [Final build](phase-6-final-build/) | ⏳ Not started |

### Phase 0: Separate control experiments
- **What:** My very first sketches. Controlling the SG90 servo and the 28BYJ-48 stepper with a joystick module, first with the built-in `Stepper` library (V1), then with `AccelStepper` (V2).
- **Why:** Before building anything I needed to know I could make each motor move at all, and get a feel for how the libraries and the joystick readings work.
- **Goal:** Joystick Y moves the servo, joystick X spins the stepper.

### Phase 1: Proof of concept
- **What:** A breadboard demo on an Arduino Nano where the servo is the barrel (up/down) and the stepper is the turret (left/right), both controlled by typed Serial Monitor commands and able to move at the same time.
- **Why:** Phase 0 showed the motors work, but they couldn't move smoothly together. The real tank needs both moving at once without one freezing the other.
- **Goal:** Both motors moving together with non-blocking code, on a proper shared 5V rail and common ground.

### Phase 2: Drive and treads
- **What:** Two DC gear motors on a tread chassis, driven by a TB6612FNG motor driver.
- **Why:** A tank has to drive. This is the first time dealing with bigger motors and a real battery.
- **Goal:** Forward, reverse and turning in place, powered from the battery through the buck converter.

### Phase 3: Wireless control
- **What:** Move the brains to an ESP32 and control everything over Bluetooth from my phone.
- **Why:** Bluetooth is cheaper and easier than a hobby RC transmitter, and range isn't a concern for this tank.
- **Goal:** Drive, turret and barrel all controllable from the phone.

### Phase 4: Chassis integration
- **What:** Mount the turret, barrel, electronics and battery on the chassis.
- **Why:** Breadboard wiring has to survive vibration and fit inside the hull.
- **Goal:** A working tank that is still running on prototype wiring.

### Phase 5: Custom PCB
- **What:** Design a PCB that replaces the breadboard: ESP32, motor drivers, buck converter and connectors on one board.
- **Why:** Cleaner, smaller and more reliable than jumper wires, and a chance to learn PCB design.
- **Goal:** Order and assemble a board that drops into the chassis.

### Phase 6: Final build
- **What:** Final assembly, tuning and polish.
- **Why:** Finish the project properly.
- **Goal:** A finished RC tank I can drive around and show off.
