# RC Tank

📓 **Daily build blog:** [Blogs / rc-tank-project](https://github.com/HiMyNamesSeb/Blogs/tree/main/rc-tank-project)

## What I'm building and why

I'm building a remote-controlled tank from scratch: tread drive, a turret that rotates left and right, and a barrel that tilts up and down, all controlled wirelessly from my phone over Bluetooth.

This is my first real electronics project. I want to actually understand how the pieces work (motors, drivers, power, microcontrollers) instead of just buying something that already works, and I want a project I can work on day by day and look back on. It started on a breadboard with my starter kit, and the loose idea is to end up with a custom PCB and a finished tank, figuring out the steps in between as I go.

> **Transparency note:** This is my first real electronics project, and I'm building it with a lot of help. I do the physical work myself: wiring, assembly, testing and debugging on the bench. **Claude (an AI assistant by Anthropic) heavily helps me write the code** and also helps write and format this repo and the blog. I'm also learning from online electrical engineering tutorials. My own early sketches (Phase 0) are marked as mine.

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
- [ ] Custom PCB `(not bought yet)`
- [x] Jumper wires / Dupont cables `(already have in kit)`

## Phases

I don't plan phases ahead. Each one gets added here when I actually start it, named for what I ended up doing (building, debugging, cleaning up, whatever it turns out to be).

| # | Phase | Status |
|---|---|---|
| 0 | [Separate control experiments](phase-0-separate-control/) | ✅ Done |
| 1 | [Proof of concept: barrel + turret demo](phase-1-proof-of-concept/) | ✅ Done |

### Phase 0: Separate control experiments
- **What:** My very first sketches. Controlling the SG90 servo and the 28BYJ-48 stepper with a joystick module, first with the built-in `Stepper` library (V1), then with `AccelStepper` (V2).
- **Why:** Before building anything I needed to know I could make each motor move at all, and get a feel for how the libraries and the joystick readings work.
- **Goal:** Joystick Y moves the servo, joystick X spins the stepper.

### Phase 1: Proof of concept
- **What:** A breadboard demo on an Arduino Nano where the servo is the barrel (up/down) and the stepper is the turret (left/right), both controlled by typed Serial Monitor commands and able to move at the same time.
- **Why:** Phase 0 showed the motors work, but they couldn't move smoothly together. The real tank needs both moving at once without one freezing the other.
- **Goal:** Both motors moving together with non-blocking code, on a proper shared 5V rail and common ground.

_The next phase gets added when it starts._
