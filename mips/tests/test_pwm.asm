# =============================================================================
# test_pwm.asm - Tests for the angle-to-pulse routine in pwm.asm
#
# Purpose : Calls angle_to_pulse with known angles and checks the results.
# Owner   : MIPS team
# Run     : java -jar tools/Mars.jar nc sm mips/tests/test_pwm.asm mips/pwm.asm
#           (or open both in MARS GUI with "assemble all files" on)
# =============================================================================

# Test cases:
#   angle 0   -> 500
#   angle 90  -> 1500
#   angle 180 -> 2500

        .data
angles:     .word 0, 90, 180
expected:   .word 500, 1500, 2500
str_arrow:  .asciiz " -> "
str_pass:   .asciiz "  PASS\n"
str_fail:   .asciiz "  FAIL\n"

        .text
        .globl main
main:
        li   $s0, 0                 # i = 0

loop:
        bge  $s0, 3, done           # 3 test cases
        sll  $t0, $s0, 2            # offset = i * 4
        lw   $s1, angles($t0)       # angle
        lw   $s2, expected($t0)     # expected pulse

        move $a0, $s1
        jal  angle_to_pulse         # $v0 = pulse
        move $s3, $v0

        # print "<angle> -> <pulse>"
        move $a0, $s1
        li   $v0, 1                 # print_int
        syscall
        la   $a0, str_arrow
        li   $v0, 4                 # print_string
        syscall
        move $a0, $s3
        li   $v0, 1
        syscall

        # print PASS / FAIL
        la   $a0, str_pass
        beq  $s3, $s2, print_result
        la   $a0, str_fail
print_result:
        li   $v0, 4
        syscall

        addi $s0, $s0, 1            # i++
        j    loop

done:
        li   $v0, 10                # exit
        syscall
