#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

//****************************************************
// Setup both motors STEP as OUTPUT, DIR as OUTPUT
// ***************************************************
void setup_motors();

//****************************************************
// Move the motor a certain number of steps
// ***************************************************
void move_steps(int steps, int dir, int motor);

//****************************************************
// Move to a location, currently set as step location,
// we could change it to be a chess coordinate.
// ***************************************************
void move_to_location(int x, int y, int curr_x, int curr_y);

//****************************************************
// Return to a home location, currently set to 0, 570.
// This shold be on the AIs side, in the middle
// ***************************************************
void return_to_home(int cur_x, int curr_y);
