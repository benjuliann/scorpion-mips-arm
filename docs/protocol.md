# Serial Protocol

> **Note:** All values in this document are **defaults**. The team may change them later; update this file when they do.

## Overview

```
keyboard -> bridge.py -> (stdin) MARS running scorpion.asm -> (stdout command lines)
         -> bridge.py -> (USB serial, 115200) -> ESP32 firmware -> servo PWM (50 Hz)
```

- `scorpion.asm` (MIPS) produces command lines, with angles already clamped and converted to pulse widths.
- `bridge.py` checks each line and forwards it to the ESP32 over serial.
- The ESP32 firmware parses each line, drives the servos, and replies with one line per command.

## Transport

| Setting     | Default                     |
|-------------|-----------------------------|
| Link        | USB serial                  |
| Baud        | 115200                      |
| Framing     | 8N1                         |
| Encoding    | ASCII                       |
| Terminator  | `\n` (newline)              |

## Joints

| ID | Joint       |
|----|-------------|
| 0  | base        |
| 1  | shoulder    |
| 2  | elbow       |
| 3  | wrist pitch |
| 4  | wrist roll  |
| 5  | gripper     |

Kit: diymore ROT3U 6DOF aluminium arm with MG996 servos (one servo per joint).

## Message format

Bridge -> ESP32, one command per line:

| Command            | Meaning                                  | Example      |
|--------------------|------------------------------------------|--------------|
| `J<id>:<pulse_us>` | Set joint `<id>` to pulse width in µs    | `J1:1500\n`  |
| `HOME`             | Move all joints to home position         | `HOME\n`     |
| `PING`             | Status request                           | `PING\n`     |

### Pulse range

- Default range: **500–2500 µs**. The 50 Hz period is 20000 µs.
- Per-joint safe limits are in `firmware/scorpion_esp32/config.h` and must stay inside 500–2500 µs.

### Angle -> pulse conversion (done in MIPS, integer math)

```
pulse_us = 500 + (angle * 2000) / 180      ; angle in 0..180
```

| Angle | Pulse (µs) |
|-------|------------|
| 0     | 500        |
| 90    | 1500       |
| 180   | 2500       |

### Failsafe

If the ESP32 gets no valid command for **N ms (default 2000)**, it **holds position**. It does not snap home unless the team decides otherwise.

## Replies

The ESP32 sends exactly one reply line per command it receives:

| Reply          | Meaning                     |
|----------------|-----------------------------|
| `OK\n`         | Command accepted and applied |
| `ERR <reason>\n` | Command rejected          |

## Error reasons

| Reason         | When                                                          |
|----------------|---------------------------------------------------------------|
| `BAD_FORMAT`   | Line does not match any known command                         |
| `BAD_JOINT`    | Joint ID is not 0–5                                           |
| `OUT_OF_RANGE` | Pulse width is outside that joint's limits in `config.h`      |

## Examples

| Sent         | Expected reply       | Notes                                   |
|--------------|----------------------|-----------------------------------------|
| `PING\n`     | `OK\n`               | Status check                            |
| `HOME\n`     | `OK\n`               | All joints to home                      |
| `J0:1500\n`  | `OK\n`               | Base to center (90°)                    |
| `J1:500\n`   | `OK\n`               | Shoulder to 0° (if inside its limits)   |
| `J5:2500\n`  | `OK\n`               | Gripper to 180° (if inside its limits)  |
| `J6:1500\n`  | `ERR BAD_JOINT\n`    | Joint 6 does not exist                  |
| `J2:3000\n`  | `ERR OUT_OF_RANGE\n` | Above 2500 µs                           |
| `J2:100\n`   | `ERR OUT_OF_RANGE\n` | Below 500 µs                            |
| `MOVE 1\n`   | `ERR BAD_FORMAT\n`   | Unknown command                         |
| `J1-1500\n`  | `ERR BAD_FORMAT\n`   | Missing `:`                             |

## Open questions

