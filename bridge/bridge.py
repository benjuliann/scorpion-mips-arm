"""bridge.py - The Scorpion: keyboard -> MARS -> ESP32 bridge.

Owner: Bridge team
Run:   python bridge/bridge.py   (from repo root)

Responsibilities:
- Launch MARS headless: java -jar Mars.jar nc mips/scorpion.asm
- Read the controller (keyboard as backup) and feed input to MARS stdin
- Read OK / ERR replies from the ESP32
- Read command lines from MARS stdout
- Validate each line against docs/protocol.md
- Forward valid lines to the ESP32 over USB serial (115200 baud)
- Handle shutdown cleanly (stop MARS, close serial)
"""

# TODO: imports (subprocess, serial, pygame for controller/keyboard, config)

import subprocess
import serial
import pygame
import config

pulse_min = 500 # 0 degrees (lowest arm can go)
pulse_max = 2500 # 180 degrees (Highest point the arm can extend)

controller_axes = {
    0: (0, 1)  # left stick X  -> base
    1: (1, -1) # left stick Y  -> shoulder (up is negative on most pads)
    2: (3, 1)  # right stick Y -> elbow
    3: (2, -1) # right stick X -> wrist pitch
}

controller_buttons = {
    0: (5, +1), 1: (5, -1),   # A / B   -> gripper
    4: (4, -1), 5: (4, +1),   # bumpers -> wrist roll)
}

def main():
    # TODO: launch MARS
    # TODO: open serial port
    # TODO: main loop: read controller/keys -> MARS stdin, MARS stdout -> validate -> serial
    # TODO: shutdown handling
    pass


if __name__ == "__main__":
    main()
