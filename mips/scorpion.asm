# =============================================================================
# scorpion.asm - The Scorpion: main MIPS program
#
# Purpose : Reads input (controller or keyboard, via bridge.py) from stdin, updates the joint table, clamps
#           angles to limits, converts angle -> pulse width, and prints
#           command lines (e.g. "J1:1500") to stdout for bridge.py.
# Owner   : MIPS team
# Run     : Launched headless by bridge/bridge.py:
#               java -jar Mars.jar nc mips/scorpion.asm
#           Can also be opened and run in the MARS GUI for testing.
# Protocol: see docs/protocol.md
# C ref   : reference/scorpion.c (hand-translated, not compiler output)
# =============================================================================

        .data
# -----------------------------------------------------------------------------
# Joint table
# TODO: per joint (0 base, 1 shoulder, 2 elbow, 3 wrist pitch,
#       4 wrist roll, 5 gripper):
#       current angle, target angle, min angle, max angle
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
# Prompts / strings
# TODO: command prefixes ("J", ":", "HOME", "PING"), newline, any messages
# -----------------------------------------------------------------------------

        .text
        .globl main
# -----------------------------------------------------------------------------
# main - main loop
# TODO: init joint table, then loop:
#       read input -> update target -> clamp -> angle-to-pulse -> output
# -----------------------------------------------------------------------------
main:

# -----------------------------------------------------------------------------
# Input handling
# TODO: read an input char from stdin (syscall), map it to joint + direction
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
# Limit clamping
# TODO: clamp target angle to the joint's min/max (see joints.asm)
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
# Angle-to-pulse call
# TODO: call the routine in pwm.asm (angle in $a0, pulse in $v0)
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
# Command-line output
# TODO: print "J<id>:<pulse_us>\n" to stdout
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
# Exit
# -----------------------------------------------------------------------------
        li   $v0, 10
        syscall
