"""servo_test.py - Sweep one servo to check wiring and limits.

Owner: Firmware / hardware team
Run:   python tools/servo_test.py   (from repo root)

Opens the serial port and slowly sweeps one chosen joint between its
limits using J<id>:<pulse_us> commands (see docs/protocol.md).
"""


def main():
    # TODO: open serial port (bridge/config.py)
    # TODO: choose joint to test
    # TODO: sweep slowly between that joint's min and max pulse
    pass


if __name__ == "__main__":
    main()
