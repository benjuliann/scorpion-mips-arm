/*
 * pwm.c - C reference for mips/pwm.asm
 *
 * Purpose : Angle-to-pulse-width routine, translated by hand into
 *           mips/pwm.asm.
 * Owner   : MIPS team
 * Run     : Built together with reference/scorpion.c (optional, PC only).
 */

/*
 * TODO: int angle_to_pulse(int angle)
 *
 *   angle : 0-180 degrees            (-> $a0 in MIPS)
 *   return: pulse width in us        (-> $v0 in MIPS)
 *
 *   Integer math only, to match MIPS (see docs/protocol.md):
 *       pulse_us = 500 + (angle * 2000) / 180
 *
 *   Expected: 0 -> 500, 90 -> 1500, 180 -> 2500
 */
int angle_to_pulse(int angle) = {
    return 500 + (angle * 2000) / 180; /* 500 = 0 degrees, 1500 = 90 degrees and 2500 = 180 degrees*/
}