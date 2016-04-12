#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

// ************************************************
// Set the magnet up as an OUTPUT
// ************************************************
void setup_magnet();

// *************************************************
// Turn magnet completely on or off
// *************************************************
void mag_on_off(int state);

// *************************************************
// PWM the magnet. Value is the duty cycle. If value
// is 984, that means 98.4 percent.
// This will probably be done through Verilog
// because of speed.
// *************************************************
void pwm_mag(int value);
