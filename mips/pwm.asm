# =============================================================================
# pwm.asm - Angle-to-pulse-width routine
#
# Purpose : Converts a servo angle (0-180) to a pulse width in microseconds.
# Owner   : MIPS team
# C ref   : reference/pwm.c (hand-translated, not compiler output)
# Run     : Not run on its own. Assembled together with scorpion.asm.
#           Tested by mips/tests/test_pwm.asm.
# =============================================================================

# TODO: angle_to_pulse
#
#   Calling convention:
#       Argument : $a0 = angle in degrees (0-180)
#       Result   : $v0 = pulse width in microseconds
#
#   Formula (integer math, see docs/protocol.md):
#       pulse_us = 500 + (angle * 2000) / 180
#
#   Expected: 0 -> 500, 90 -> 1500, 180 -> 2500
