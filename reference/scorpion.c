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

#include <stdio.h>

/* joints.c */
int  get_target(int joint);
void set_target(int joint, int angle);
void set_current(int joint, int angle);
int  clamp(int joint, int angle);

/* pwm.c */
int angle_to_pulse(int angle);

/* ---------------------------------------------------------------------------
 * Joint table  (-> .data in scorpion.asm, one .word array each)
 * Index: 0 base, 1 shoulder, 2 elbow, 3 wrist pitch, 4 wrist roll, 5 gripper
 * All joints start at 90 (center). TODO: tune min/max per joint on the arm.
 * ------------------------------------------------------------------------- */
int current_angle[6] = { 90,  90,  90,  90,  90,  90};
int target_angle[6]  = { 90,  90,  90,  90,  90,  90};
int min_angle[6]     = {  0,   0,   0,   0,   0,   0};
int max_angle[6]     = {180, 180, 180, 180, 180, 180};

#define STEP 5      /* degrees moved per key press */

/* ---------------------------------------------------------------------------
 * Strings  (-> .data in scorpion.asm, .asciiz)
 * Key for joint j is up_keys[j] (+STEP) or down_keys[j] (-STEP).
 *   q/a base, w/s shoulder, e/d elbow, r/f wrist pitch, t/g wrist roll,
 *   y/h gripper, x quits.
 * ------------------------------------------------------------------------- */
char up_keys[]   = "qwerty";
char down_keys[] = "asdfgh";

/* ---------------------------------------------------------------------------
 * Input handling
 * find_key: return the index of c in keys (0-5), or -1 if not found.
 * (-> $a0 = keys address, $a1 = c, $v0 = index)
 * ------------------------------------------------------------------------- */
int find_key(char keys[], int c) {
    for (int i = 0; i < 6; i++) {
        if (keys[i] == c) {
            return i;
        }
    }
    return -1;
}

/* ---------------------------------------------------------------------------
 * main - main loop  (-> main: in scorpion.asm)
 * read input -> update target -> clamp -> angle-to-pulse -> output
 * ------------------------------------------------------------------------- */
int main(void) {
    while (1) {
        int c = getchar();                  /* MARS: syscall 12 (read char) */
        if (c == EOF || c == 'x') {
            break;
        }

        int step = STEP;
        int joint = find_key(up_keys, c);
        if (joint == -1) {
            step = -STEP;
            joint = find_key(down_keys, c);
        }
        if (joint == -1) {
            continue;                       /* ignore other chars, e.g. '\n' */
        }

        /* Limit clamping (joints.c) */
        int angle = clamp(joint, get_target(joint) + step);
        set_target(joint, angle);

        /* Angle-to-pulse call (pwm.c) */
        int pulse = angle_to_pulse(angle);

        /* Command-line output: "J<id>:<pulse_us>\n"
         * MARS: print "J", print_int joint, print ":", print_int pulse, "\n" */
        printf("J%d:%d\n", joint, pulse);

        set_current(joint, angle);
    }
    return 0;                               /* MARS: syscall 10 (exit) */
}
