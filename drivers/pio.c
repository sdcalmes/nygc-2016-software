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
// !!!! NOTE !!!!!!!
// EACH function should follow the same basic format that is shown below
//*****************************************************************************
// fd = open("/path/to/file");
//
// if you are writing a value
// write(fd,"string to write", string_len);
//
// Or if you are reading a value
// read(fd, &value, 1);
//
// close(fd);

//*****************************************************************************
// Write the value of gpio_pin to /sys/class/gpio/export to enable access to 
// a specific GPIO pin.  You will need to convert the gpio_pin to a string 
// before you write the value to the file handle.
//*****************************************************************************
void pio_enable(int gpio_pin)
{
  int gpio_fd;
  gpio_fd = open("/sys/class/gpio/export", O_WRONLY | O_APPEND);
  char buffer[10];
  snprintf(buffer, 10, "%d", gpio_pin);
  write(gpio_fd, buffer, sizeof(buffer));
  close(gpio_fd);
  
}

//*****************************************************************************
// Write the value of gpio_pin to /sys/class/gpio/unexport to enable access to 
// a specific GPIO pin.  You will need to convert the gpio_pin to a string 
// before you write the value to the file handle.
//*****************************************************************************
void pio_disable(int gpio_pin)
{
  int gpio_fd;
  gpio_fd = open("/sys/class/gpio/export", O_WRONLY | O_APPEND);
  char buffer[10];
  snprintf(buffer, 10, "%d", gpio_pin);
  write(gpio_fd, buffer, sizeof(buffer));
  close(gpio_fd);

}

//*****************************************************************************
// Write either "in" or "out" to the direction file handle of the specified GPIO
// pin.  Use the sprintf function to determine the correct file path name 
// of the gpio pin
//*****************************************************************************
void pio_set_direction(int gpio_pin, int dir)
{

  int gpio_fd;
  char file_name[100];
  sprintf(file_name, "/sys/class/gpio/gpio%d/direction", gpio_pin);
  gpio_fd = open(file_name, O_WRONLY | O_TRUNC);
  if(dir == 0){
    write(gpio_fd, "out", sizeof("out"));
  }
  else {
    write(gpio_fd, "in", sizeof("in"));
  }

  close(gpio_fd);

}

//*****************************************************************************
// Write either "2" or "0" to the value file handle of the specified GPIO
// pin.  Use the sprintf function to determine the correct file path name 
// of the gpio pin
//*****************************************************************************
void pio_set_value(int gpio_pin, int out)
{
  int gpio_fd;
  char file_name[100];
  char buffer[sizeof(out)];
  sprintf(file_name, "/sys/class/gpio/gpio%d/value", gpio_pin);
  snprintf(buffer, sizeof(out), "%d", out);
  gpio_fd = open(file_name, O_WRONLY);
  write(gpio_fd, buffer, sizeof(buffer));
  close(gpio_fd);
}

//*****************************************************************************
// Read in the value of the GPIO pin using the value file handle.
// pin.  Use the sprintf function to determine the correct file path name 
// of the gpio pin
//*****************************************************************************
bool pio_get_value(int gpio_pin)
{

  int gpio_fd;
  char file_name[100];
  sprintf(file_name, "/sys/class/gpio/gpio%d/value", gpio_pin);
  gpio_fd = open(file_name, O_RDONLY);
  char val;
  read(gpio_fd, &val, 1);
  close(gpio_fd);
  int i = val - '0';
  if(i == 1){
    return true;
  } else {
    return false;
  }

}
