/*
 * scorpion.c - C reference for mips/scorpion.asm
 *
 * Purpose : Reference version of the main program, written first in C and
 *           then translated BY HAND into mips/scorpion.asm. Not compiled to
 *           MIPS, and not part of the running system.
 * Owner   : MIPS team
 * Run     : Optional, on a PC for checking logic, e.g.
 *               gcc reference/scorpion.c reference/joints.c reference/pwm.c
 *           Reads input chars from stdin and prints command lines to stdout, the
 *           same way the MIPS program does under MARS.
 * Protocol: see docs/protocol.md
 */

/* TODO: includes */

/* ---------------------------------------------------------------------------
 * Joint table  (-> .data in scorpion.asm)
 * TODO: per joint (0 base, 1 shoulder, 2 elbow, 3 wrist pitch,
 *       4 wrist roll, 5 gripper):
 *       current angle, target angle, min angle, max angle
 * ------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------
 * Strings  (-> .data in scorpion.asm)
 * TODO: command prefixes ("J", ":", "HOME", "PING"), newline, any messages
 * ------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------
 * Input handling
 * TODO: read an input char from stdin, map it to joint + direction
 * ------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------
 * Limit clamping
 * TODO: clamp target angle to the joint's min/max (see joints.c)
 * ------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------
 * Angle-to-pulse call
 * TODO: call angle_to_pulse() in pwm.c
 * ------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------
 * Command-line output
 * TODO: print "J<id>:<pulse_us>\n" to stdout
 * ------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------
 * main - main loop  (-> main: in scorpion.asm)
 * TODO: init joint table, then loop:
 *       read input -> update target -> clamp -> angle-to-pulse -> output
 * ------------------------------------------------------------------------- */
int main(void) {
    return 0;
}
