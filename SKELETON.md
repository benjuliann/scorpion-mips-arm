# Task: Scaffold the `scorpion-mips-arm` repo
 
You are working in the repo root of **scorpion-mips-arm** (The Scorpion: a MIPS-assembly-controlled claw-style robot arm, driven through a Python bridge and an ESP32).

Hardware: diymore ROT3U 6DOF aluminium arm kit with 6 MG996 servos. Servos are powered from a separate 5-6 V supply (around 10 A) whose ground is shared with the ESP32.
 
## Already done by the user (do NOT overwrite)
- The folder structure
- `.gitignore`
- `README.md`
Before creating anything, run `ls -R` (ignoring `.git`) and check what already exists. **Never overwrite an existing file.** If a file already exists, skip it and list it in your final report.
 
## Ground rules
1. **Create skeleton files only. Do not implement logic.** The team writes the real code.
2. Code files get only: a header comment (purpose, owner area, how it's run), section comments or TODO markers describing what goes where, and the minimum boilerplate needed for the file to be valid (see per-file notes).
3. Documentation files (`docs/*.md`) get real content where specified below.
4. Do not install anything, do not run git commands that modify history, do not commit. Leave the changes uncommitted for the user to review.
5. Keep placeholder text short and factual. No invented specs beyond the defaults listed in this file.
## Architecture (for your context)
```
controller (keyboard backup) -> bridge.py -> (stdin) MARS running scorpion.asm -> (stdout command lines)
         -> bridge.py -> (USB serial, 115200) -> ESP32 firmware -> servo PWM (50 Hz)
```
- MIPS (`scorpion.asm`) owns: joint table, input handling, limit clamping, angle -> pulse-width conversion, formatting command lines.
- `bridge.py` owns: launching MARS headless (`java -jar Mars.jar nc <file>`), reading controller input (keyboard as backup, both via `pygame`) and feeding MARS stdin, reading MARS stdout, validating lines, forwarding to serial, reading ESP32 `OK`/`ERR` replies.
- ESP32 firmware (C/C++, Arduino-style) owns: parsing serial lines and driving servos. It is NOT MIPS.
- The MIPS code is hand-written assembly, not compiler output. The main program is written first in C (`reference/`), then translated by hand into MIPS.
## Protocol defaults (write these into `docs/protocol.md`)
These are defaults the team can change later; mark them as such.
 
- Transport: USB serial, **115200 baud**, 8N1, ASCII, newline-terminated (`\n`).
- Joints (6): `0` base, `1` shoulder, `2` elbow, `3` wrist pitch, `4` wrist roll, `5` gripper.
- Command from bridge to ESP32: `J<id>:<pulse_us>\n` e.g. `J1:1500\n`
- Home all joints: `HOME\n`
- Status request: `PING\n`
- ESP32 replies, one line per command: `OK\n`, or `ERR <reason>\n` (reasons: `BAD_FORMAT`, `BAD_JOINT`, `OUT_OF_RANGE`).
- Pulse range default: 500-2500 us (50 Hz period = 20000 us). Per-joint safe limits live in `firmware/scorpion_esp32/config.h` and must be inside this range.
- Angle -> pulse (done in MIPS, integer math): `pulse_us = 500 + (angle * 2000) / 180`, angle 0-180.
- Failsafe: if the ESP32 receives no valid command for N ms (default 2000), it holds position (do not snap home unless the team decides otherwise).
- Include a small table of example messages and expected replies.
## Files to create
 
### Root
- Nothing new (README.md and .gitignore exist). If `README.md` is missing a "Repo layout" section, do NOT edit it; mention this in your report.
### `docs/`
- `protocol.md` - full content per "Protocol defaults" above, plus sections: Overview, Message format, Replies, Error reasons, Examples, Open questions (leave empty list).
- `report.md` - headings only, matching the proposal deliverables: Introduction, Development approach (one line: C first, hand-translated to MIPS), Hardware design, Input mapping, MIPS program structure, Angle-to-PWM routine, Serial protocol, Bridge script, ESP32 firmware, Testing, Results, Lessons learned. Each heading followed by `TODO`.
- `user-guide.md` - headings only: Parts list, Wiring, Software setup (MARS, Python, ESP32; links to `setup.md`), Running the program, Control chart (controller is main input, keyboard is backup; table with columns Controller | Key | Joint | Direction, rows left empty), Troubleshooting. Each followed by `TODO`.
- `setup.md` - quick install guide for the team (Windows): Git, Java, MARS 4.5 saved as `tools/Mars.jar`, Python venv + `pip install -r bridge/requirements.txt`, Arduino IDE 2 + ESP32 board package + `ESP32Servo`, USB-serial driver, setting `SERIAL_PORT`, controller, power safety, quick-check table.
- `wiring/` - create `pin-table.md` with a table (Joint | Servo | ESP32 GPIO | Notes) and the six joints, Servo column `MG996`, GPIO column set to `TBD`. Add notes: separate servo supply with shared ground; avoid GPIO 34-39 and strapping pins 0, 2, 12, 15.
### `mips/`
- `scorpion.asm` - header comment block, then labeled empty sections with TODO comments: `.data` (joint table: current angle, target angle, min, max per joint; prompts/strings), `.text` / `main` (main loop), input handling, limit clamping, angle-to-pulse call, command-line output. Include only a `main:` label and a clean exit syscall (`li $v0, 10` / `syscall`) so the file assembles in MARS. Use MARS syntax.
- `joints.asm` - header comment + TODO list of accessor routines (get/set current, get/set target, get min/max, clamp). No code beyond comments.
- `pwm.asm` - header comment + TODO describing the angle-to-pulse routine, its calling convention (argument in `$a0`, result in `$v0`), and the formula from the protocol section. No code beyond comments.
- `tests/test_pwm.asm` - header comment + TODO list of test cases (angle 0 -> 500, 90 -> 1500, 180 -> 2500). Minimal exit syscall only.
### `bridge/`
- `bridge.py` - module docstring, imports commented as TODO, a `main()` stub containing only `pass`, and the `if __name__ == "__main__":` guard. Docstring lists the responsibilities (launch MARS, read controller/keyboard, forward lines, validate, read ESP32 replies, handle shutdown).
- `config.py` - constants only: `SERIAL_PORT = "COM3"  # TODO set per machine`, `BAUD = 115200`, `MARS_JAR = "tools/Mars.jar"  # TODO`, `MIPS_PROGRAM = "mips/scorpion.asm"`, `FAILSAFE_MS = 2000`, `NUM_JOINTS = 6`, an empty `CONTROLLER_MAP = {}  # TODO button/axis -> joint/direction (main input)`, and an empty `KEY_MAP = {}  # TODO key -> joint/direction (backup input)`.
- `requirements.txt` - `pyserial` and `pygame` (controller and keyboard input).
- `tests/fake_esp32.py` - docstring + stub `main()` describing: reads lines from a given serial/pty/stdin, prints them, replies `OK`. `pass` body.
### `firmware/scorpion_esp32/`
- `scorpion_esp32.ino` - header comment, `#include "config.h"`, empty `setup()` and `loop()` with TODO comments (init Serial, attach servos, parse line, apply pulse, failsafe check). Must compile as valid Arduino code.
- `config.h` - include guard, `#define` constants: `BAUD_RATE 115200`, `NUM_JOINTS 6`, `FAILSAFE_MS 2000`, arrays or defines for pin numbers set to `-1 // TODO`, per-joint `PULSE_MIN_US`/`PULSE_MAX_US` defaulting to 500/2500 with a comment that they must be tuned per servo, and that the gripper's closed limit must stop before the claw fully closes (avoid stalling).
### `tools/`
- `servo_test.py` - docstring + stub `main()` (`pass`) describing: open serial, sweep one chosen joint between its limits slowly. TODO comments only.
- `protocol_check.py` - docstring + stub `main()` listing the sample messages from `docs/protocol.md` to send and the expected replies.
### `reference/`
C reference, written first and translated by hand into the matching `mips/` file. Comments and TODOs only.
- `scorpion.c` - same sections as `scorpion.asm`, each noting where it maps in the assembly. Only `int main(void) { return 0; }`.
- `joints.c` - TODO list of the joint accessors (matches `joints.asm`).
- `pwm.c` - TODO for `int angle_to_pulse(int angle)`: angle -> `$a0`, return -> `$v0`, integer formula, expected 0 -> 500, 90 -> 1500, 180 -> 2500.
- Each `mips/*.asm` header gets a `C ref` line pointing to its `.c` file.
### Placeholder files for otherwise-empty folders
Git does not track empty folders. If any folder in the structure ends up with no file, add an empty `.gitkeep`.
 
## Verification (do this before reporting)
1. `ls -R` the tree and confirm every file above exists (or was skipped because it already existed).
2. Syntax check: `python -m py_compile` on every `.py` file (use `-I` is not needed here; run from repo root). Remove any `__pycache__` created.
3. Confirm `docs/protocol.md` contains the defaults above and the example table.
4. Do not try to assemble the MIPS, compile the C reference, or compile the Arduino sketch; just make sure the files are syntactically plausible.
## Final report format
Reply with:
- A tree of the repo as it now stands.
- Files created vs. files skipped (already existed).
- Anything you could not do or any assumption you made beyond this file.
- One suggested next step.
Do not commit.
 