/*
 * scorpion_esp32.ino - The Scorpion: ESP32 servo firmware
 *
 * Purpose : Reads command lines over USB serial and drives the servos
 *           (50 Hz PWM). Protocol: see docs/protocol.md.
 * Owner   : Firmware team
 * Run     : Build and upload with Arduino IDE / arduino-cli to the ESP32.
 */

#include "config.h"

void setup() {
  // TODO: init Serial at BAUD_RATE
  // TODO: attach servos to pins in config.h
}

void loop() {
  // TODO: read and parse a serial line (J<id>:<pulse_us>, HOME, PING)
  // TODO: apply pulse to the servo, reply OK / ERR <reason>
  // TODO: failsafe check (no valid command for FAILSAFE_MS -> hold position)
}
