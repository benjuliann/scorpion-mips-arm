"""config.py - Bridge settings. Defaults; see docs/protocol.md."""

SERIAL_PORT = "COM3"  # TODO set per machine
BAUD = 115200
MARS_JAR = "tools/Mars.jar"  # TODO
MIPS_PROGRAM = "mips/scorpion.asm"
FAILSAFE_MS = 2000
NUM_JOINTS = 6  # 0 base, 1 shoulder, 2 elbow, 3 wrist pitch, 4 wrist roll, 5 gripper
CONTROLLER_MAP = {}  # TODO button/axis -> joint/direction (main input)
KEY_MAP = {}  # TODO key -> joint/direction (backup input)
