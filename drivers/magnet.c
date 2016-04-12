// Sam Calmes, Jake Schieber, Tara Abernathy, Tofe Salako
// Magnet driver
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

static int GPIO_IN = 1;
static int GPIO_OUT = 0;
//TODO
static int MAGNET_PIO = 0;

void setup_magnet()
{
	pio_enable(MAGNET_PIO);
	pio_set_direction(MAGNET_PIO, GPIO_OUT);
}

void mag_on_off(int state)
{
	pio_set_value(MAGNET_PIO, state);
}

//mag pwm will be done through verilog
