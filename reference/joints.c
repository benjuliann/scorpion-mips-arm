/*
 * joints.c - C reference for mips/joints.asm
 *
 * Purpose : Joint table accessor routines, translated by hand into
 *           mips/joints.asm.
 * Owner   : MIPS team
 * Run     : Built together with reference/scorpion.c (optional, PC only).
 *
 * The joint table is four int arrays of 6 entries each (one per joint),
 * defined in scorpion.c (-> .data in scorpion.asm). Each array is a word
 * array in MIPS, so joint j is at  label + j*4.
 *
 * Calling convention (all routines):
 *     $a0 = joint id (0-5)
 *     $a1 = angle    (setters / clamp only)
 *     $v0 = result   (getters / clamp only)
 */

extern int current_angle[6];
extern int target_angle[6];
extern int min_angle[6];
extern int max_angle[6];

/* get_current - return current angle of joint */
int get_current(int joint) {
    return current_angle[joint];
}

/* set_current - set current angle of joint */
void set_current(int joint, int angle) {
    current_angle[joint] = angle;
}

/* get_target - return target angle of joint */
int get_target(int joint) {
    return target_angle[joint];
}

/* set_target - set target angle of joint */
void set_target(int joint, int angle) {
    target_angle[joint] = angle;
}

/* get_min - return min angle of joint */
int get_min(int joint) {
    return min_angle[joint];
}

/* get_max - return max angle of joint */
int get_max(int joint) {
    return max_angle[joint];
}

/* clamp - clamp an angle to a joint's min/max */
int clamp(int joint, int angle) {
    if (angle < min_angle[joint]) {
        return min_angle[joint];
    }
    if (angle > max_angle[joint]) {
        return max_angle[joint];
    }
    return angle;
}
