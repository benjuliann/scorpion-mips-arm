/*
 * test_reference.c - Tests for reference/joints.c and reference/pwm.c
 *
 * Purpose : Checks angle_to_pulse and the joint accessors with known values.
 * Owner   : MIPS team
 * Run     : gcc reference/tests/test_reference.c reference/joints.c reference/pwm.c -o test_reference
 *           ./test_reference      (exit code 0 = all passed)
 */

#include <stdio.h>

/* joints.c */
int  get_current(int joint);
void set_current(int joint, int angle);
int  get_target(int joint);
void set_target(int joint, int angle);
int  get_min(int joint);
int  get_max(int joint);
int  clamp(int joint, int angle);

/* pwm.c */
int angle_to_pulse(int angle);

/* Test joint table (joint 0 has narrower limits to test clamp) */
int current_angle[6] = { 90,  90,  90,  90,  90,  90};
int target_angle[6]  = { 90,  90,  90,  90,  90,  90};
int min_angle[6]     = { 10,   0,   0,   0,   0,   0};
int max_angle[6]     = {170, 180, 180, 180, 180, 180};

int failures = 0;

void check(const char *name, int got, int expected) {
    if (got == expected) {
        printf("PASS  %-24s %d\n", name, got);
    } else {
        printf("FAIL  %-24s got %d, expected %d\n", name, got, expected);
        failures++;
    }
}

int main(void) {
    /* pwm.c */
    check("angle_to_pulse(0)",   angle_to_pulse(0),   500);
    check("angle_to_pulse(90)",  angle_to_pulse(90),  1500);
    check("angle_to_pulse(180)", angle_to_pulse(180), 2500);

    /* joints.c getters */
    check("get_current(0)", get_current(0), 90);
    check("get_min(0)",     get_min(0),     10);
    check("get_max(0)",     get_max(0),     170);

    /* joints.c setters */
    set_target(2, 45);
    check("set_target(2, 45)",  get_target(2), 45);
    set_current(3, 120);
    check("set_current(3, 120)", get_current(3), 120);

    /* clamp */
    check("clamp(0, 5)   below min", clamp(0, 5),   10);
    check("clamp(0, 200) above max", clamp(0, 200), 170);
    check("clamp(0, 90)  in range",  clamp(0, 90),  90);

    printf("%d failure(s)\n", failures);
    return failures != 0;
}
