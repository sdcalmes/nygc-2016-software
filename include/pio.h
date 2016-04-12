#ifndef __PIO_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

//*****************************************************************************
// Enables access to a specified GPIO pin
//*****************************************************************************
void pio_enable(int gpio_pin);

//*****************************************************************************
// Disabled  access to a specified GPIO Pin
//*****************************************************************************
void pio_disable(int gpio_pin);

//*****************************************************************************
// A non-zero value of dir will set the direction to an input
// A zero value of dir will set the direction to an output
//*****************************************************************************
void pio_set_direction(int gpio_pin, int dir);

//*****************************************************************************
// Any non-zero value of out will result in a 1 being written to the GPIO pin
// A zero value of out will result in a 0 being written to the GPIO pin
//*****************************************************************************
void pio_set_value(int gpio_pin, int out);

//*****************************************************************************
//*****************************************************************************
bool pio_get_value(int gpio_pin);

#endif

