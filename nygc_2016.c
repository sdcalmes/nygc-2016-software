/*
# ############################################################################ #
#									       #
# Authors: Sam Calmes, Tara Abernathy, Tofe Salako, Jake Schieber              #
#                                                                              #
# NYGC Main program. Handles motor,magnet, bluetooth, etc logic. Sends data    #
# over bluetooth to mobile phone. Keeps string of board "position". View       #
# example board positions on chessboard.js website to get an idea of how they  #
# should be layed out.							       #
#									       #
# ############################################################################ #
*/



#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>



int main(int argc, char *argv[])
{
	printf("Welcome to NYGC.\n");

	//main will have to run *forever
	while(1)
	{
		//whenever we send position data over bluetooth, we should
		//print it out.
		//whenever we receive data from bluetooth, we should print
		//

	}

}
