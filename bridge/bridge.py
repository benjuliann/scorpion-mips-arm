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


def main():
    # TODO: launch MARS
    # TODO: open serial port
    # TODO: main loop: read controller/keys -> MARS stdin, MARS stdout -> validate -> serial
    # TODO: shutdown handling
    pass


if __name__ == "__main__":
    main()
