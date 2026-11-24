# Pin Table

Kit: diymore ROT3U 6DOF aluminium arm, MG996 servos.

| Joint           | Servo | ESP32 GPIO | Notes |
|-----------------|-------|------------|-------|
| 0 - base        | MG996 | TBD        |       |
| 1 - shoulder    | MG996 | TBD        |       |
| 2 - elbow       | MG996 | TBD        |       |
| 3 - wrist pitch | MG996 | TBD        |       |
| 4 - wrist roll  | MG996 | TBD        |       |
| 5 - gripper     | MG996 | TBD        |       |

## Notes
- Servos are powered from a separate 5-6 V supply (around 10 A), not from the ESP32. Supply ground and ESP32 ground must be connected.
- Do not use GPIO 34-39 (input only) or boot strapping pins (0, 2, 12, 15) for servos.
