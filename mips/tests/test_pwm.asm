# =============================================================================
# test_pwm.asm - Tests for the angle-to-pulse routine in pwm.asm
#
# Purpose : Calls angle_to_pulse with known angles and checks the results.
# Owner   : MIPS team
# Run     : java -jar Mars.jar nc mips/tests/test_pwm.asm
#           (or open in MARS GUI)
# =============================================================================

# TODO test cases:
#   angle 0   -> 500
#   angle 90  -> 1500
#   angle 180 -> 2500

        .text
        .globl main
main:
        li   $v0, 10
        syscall
