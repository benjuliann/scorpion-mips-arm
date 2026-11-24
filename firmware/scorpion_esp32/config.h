/*
 * config.h - The Scorpion: firmware settings.
 * Defaults; see docs/protocol.md.
 * Kit: diymore ROT3U 6DOF arm, MG996 servos.
 */

#ifndef SCORPION_CONFIG_H
#define SCORPION_CONFIG_H

#define BAUD_RATE   115200
#define NUM_JOINTS  6
#define FAILSAFE_MS 2000

// Servo pins: 0 base, 1 shoulder, 2 elbow, 3 wrist pitch, 4 wrist roll, 5 gripper
#define PIN_BASE        -1  // TODO
#define PIN_SHOULDER    -1  // TODO
#define PIN_ELBOW       -1  // TODO
#define PIN_WRIST_PITCH -1  // TODO
#define PIN_WRIST_ROLL  -1  // TODO
#define PIN_GRIPPER     -1  // TODO

// Per-joint pulse limits in microseconds.
// Must be tuned per servo on the real arm, and must stay within 500-2500.
// Gripper: set the "closed" limit before the claw fully closes, so it
// does not stall on an object.
#define PULSE_MIN_US_BASE        500
#define PULSE_MAX_US_BASE        2500
#define PULSE_MIN_US_SHOULDER    500
#define PULSE_MAX_US_SHOULDER    2500
#define PULSE_MIN_US_ELBOW       500
#define PULSE_MAX_US_ELBOW       2500
#define PULSE_MIN_US_WRIST_PITCH 500
#define PULSE_MAX_US_WRIST_PITCH 2500
#define PULSE_MIN_US_WRIST_ROLL  500
#define PULSE_MAX_US_WRIST_ROLL  2500
#define PULSE_MIN_US_GRIPPER     500
#define PULSE_MAX_US_GRIPPER     2500

#endif  // SCORPION_CONFIG_H
