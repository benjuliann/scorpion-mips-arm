"""fake_esp32.py - Stand-in for the ESP32 when testing the bridge.

Owner: Bridge team
Run:   python bridge/tests/fake_esp32.py

Reads lines from a given serial port, pty, or stdin, prints each line,
and replies "OK" to each one.
"""


def main():
    # TODO: choose input source (serial port / pty / stdin)
    # TODO: read lines, print them, reply "OK"
    pass


if __name__ == "__main__":
    main()
