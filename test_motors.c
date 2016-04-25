
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "include/pio.h"

#define GPIO_NUM 480

static int MOTOR_2_STEP = 13;
static int MOTOR_2_DIR = 12;

int main(int argc, char *argv[]){
  
  pio_enable(GPIO_NUM + MOTOR_2_STEP);
  pio_enable(GPIO_NUM + MOTOR_2_DIR);
  pio_set_direction(GPIO_NUM + MOTOR_2_STEP, 0);
  pio_set_direction(GPIO_NUM + MOTOR_2_DIR, 0);
  pio_set_value(GPIO_NUM + MOTOR_2_STEP, 0);
  pio_set_value(GPIO_NUM + MOTOR_2_DIR, 0);


  int i = 0;
  pio_set_value(GPIO_NUM + MOTOR_2_DIR, 1);
  for(i; i < 100; i++){
    pio_set_value(GPIO_NUM + MOTOR_2_STEP, 1);
    usleep(500);
    pio_set_value(GPIO_NUM + MOTOR_2_STEP, 0);
    usleep(500);
    pio_set_value(GPIO_NUM + MOTOR_2_STEP, 1);
    usleep(500);
    pio_set_value(GPIO_NUM + MOTOR_2_STEP, 0);

    usleep(10000);
  }

  pio_disable(GPIO_NUM + MOTOR_2_STEP);
  pio_disable(GPIO_NUM + MOTOR_2_DIR);
}
