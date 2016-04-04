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


//arguments could be how the game is set up.
// have an argument for ai v ai.
// might need arguments to setup bluetooth
int main(int argc, char *argv[])
{
	printf("Welcome to NYGC.\n");

	//main will have to run *forever
	while(1)
	{
		//whenever we send position data over bluetooth, we should
		//print it out.
		//whenever we receive data from bluetooth, we should print
		//suggested data to send is the same type of string that
		//chessboard.js uses. 

		//setup gpio's.

		//setup bluetooth to connect to phone

		//start game
			//check board for initial setup
			
			//print out which players turn it is.

			//poll for changes in capsense, need to keep the board
			//in software so we know which pieces are moved.
			//a 2-d array of booleans should work just fine.
			//then have a function that converts the 2d array to 
			//chessboard.js string. Or maybe have a 2d array for
			//each piece type.

			//once there is a change in capsense, send it to server

			//wait for response from server with AI/user move

			//do it all over again. Let the server handle bad moves
			//etc.

	}

}
