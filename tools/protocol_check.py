"""protocol_check.py - Send sample messages to the ESP32 and check replies.

Owner: Firmware / bridge team
Run:   python tools/protocol_check.py   (from repo root)

Sample messages (from docs/protocol.md) and expected replies:

    PING        -> OK
    HOME        -> OK
    J0:1500     -> OK
    J1:500      -> OK               (if inside joint limits)
    J5:2500     -> OK               (if inside joint limits)
    J6:1500     -> ERR BAD_JOINT
    J2:3000     -> ERR OUT_OF_RANGE
    J2:100      -> ERR OUT_OF_RANGE
    MOVE 1      -> ERR BAD_FORMAT
    J1-1500     -> ERR BAD_FORMAT
"""


def main():
    # TODO: open serial port
    # TODO: send each sample message, compare reply to expected, report
    pass


if __name__ == "__main__":
    main()
