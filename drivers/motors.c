// Sam Calmes, Jake Schieber, Tara Abernathy, Tofe Salako
// 2016


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "../include/pio.h"
#define GPIO_NUM 480

static int GPIO_IN = 1;
static int GPIO_OUT = 0;
//TODO
static int MOTOR_1 = 0;
static int MOTOR_2 = 1;
static int MOTOR_1_STEP = 13;
static int MOTOR_1_DIR = 12;
static int MOTOR_2_STEP = 9;
static int MOTOR_2_DIR = 11;

void setup_motors()
{
	pio_enable(GPIO_NUM + MOTOR_1_STEP);
	pio_enable(GPIO_NUM + MOTOR_2_STEP);
	pio_enable(GPIO_NUM + MOTOR_1_DIR);
	pio_enable(GPIO_NUM + MOTOR_2_DIR);
	pio_set_direction(GPIO_NUM + MOTOR_1_STEP, GPIO_OUT); 
	pio_set_direction(GPIO_NUM + MOTOR_2_STEP, GPIO_OUT);
	pio_set_direction(GPIO_NUM + MOTOR_1_DIR, GPIO_OUT);
	pio_set_direction(GPIO_NUM + MOTOR_2_DIR, GPIO_OUT);
        pio_set_value(GPIO_NUM + MOTOR_1_STEP, 0);
        pio_set_value(GPIO_NUM + MOTOR_2_STEP, 0);
        pio_set_value(GPIO_NUM + MOTOR_1_DIR, 0);
        pio_set_value(GPIO_NUM + MOTOR_2_DIR, 0);
}

void move_steps(int steps_x, int steps_y, int dir_x, int dir_y)
{
	int i = 0;
	int stepPin;
	int dirPin;
        int steps_max;
        if(steps_x >= steps_y)
          steps_max = steps_x;
        else
          steps_max = steps_y;

        pio_set_value(GPIO_NUM + MOTOR_1_DIR, dir_x);
        pio_set_value(GPIO_NUM + MOTOR_2_DIR, dir_y);
	for(i; i < steps_max; i++){
		//write 1 to move one step
		pio_set_value(GPIO_NUM + MOTOR_1_STEP, 1);
		pio_set_value(GPIO_NUM + MOTOR_2_STEP, 1);
                usleep(500);
		//need to reset value to 0
		pio_set_value(GPIO_NUM + MOTOR_1_STEP, 0);
		pio_set_value(GPIO_NUM + MOTOR_2_STEP, 0);
                usleep(500);
                pio_set_value(GPIO_NUM + MOTOR_1_STEP, 1);
		pio_set_value(GPIO_NUM + MOTOR_2_STEP, 1);
                usleep(500);
		//need to reset value to 0
		pio_set_value(GPIO_NUM + MOTOR_1_STEP, 0);
		pio_set_value(GPIO_NUM + MOTOR_2_STEP, 0);

		//delay 6ms 
		usleep(10000);
	}
}

//basically 1140x1140 steps across each way.
//location could be step location, or chess coordinate
//need to keep location in nygc_main, should return location here?
void move_to_location(int x, int y, int curr_x, int curr_y)
{
	int dir_x, dir_y;	
	int x_steps = abs(curr_x - x);
	int y_steps = abs(curr_y - y);

	if (curr_x > x)
		dir_x = 0;
	else
		dir_x = 1;

	if(curr_y > y)
		dir_y = 0;
	else
		dir_y = 1;

	//move_steps(x_steps, dir_x, MOTOR_1);
	//move_steps(y_steps, dir_y, MOTOR_2);


}

void return_to_home(int curr_x, int curr_y)
{
	//move_to_location(0, 570, curr_x, curr_y);
	
}

