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

//#include any h driver files
#include "include/motors.h"
#include "include/magnet.h"
#include "include/pio.h"

//Globals
int DEBUG = 0;
//are pieces there or not?
static int starting_board[8][8] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}
};

//give each piece type a value..what about black or white?
static int starting_board1[8][8] = {
	{12, 13, 14, 15, 16, 14, 13, 12},
	{11, 11, 11, 11, 11, 11, 11, 11},
	{30, 30, 30, 30, 30, 30, 30, 30},
	{30, 30, 30, 30, 30, 30, 30, 30},
	{30, 30, 30, 30, 30, 30, 30, 30},
	{30, 30, 30, 30, 30, 30, 30, 30},
	{21, 21, 21, 21, 21, 21, 21, 21},
	{22, 23, 24, 26, 25, 24, 23, 22}
};

//the board could also be represented as a string if need be...
char starting_board2[] = "rkbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

int current_board[8][8];
int current_x = 0;
int current_y = 0;


void print_curr_loc();
void print_board();
void setup_bluetooth();
void check_init();
//arguments could be how the game is set up.
// have an argument for ai v ai.
// might need arguments to setup bluetooth
int main(int argc, char *argv[])
{
	if(argc > 1){
		if(!strcmp(argv[1], "debug")){
			DEBUG = 1;
			printf("!!!!!!!!!!!!!DEBUG MODE ON!!!!!!!!!!!!!!\n\n\n");
		}
	}
	char a;
	//*************************************************************************
	//INITIAL GAME SETUP AND CHECKS
	//*************************************************************************
	printf("Preparing to start game..\n");
	setup_bluetooth();
	setup_motors();
	if(!DEBUG){
		check_init();
	} else {
		printf("In debug mode! Assuming everything is correct!\n");
	}
	//*************************************************************************
	//************************************************************************

	//Copy the starting board array to the current board.
	memcpy(current_board, starting_board1, sizeof(int) * 8 * 8);

	//Ask the user to make sure the motors are in the correct corners..not sure which yet.
	if(!DEBUG){
		printf("Make sure 2D Plotter is in the correct corner!\n");
		printf("Are the motors in the correct corners and are we ready to start the game? (Y/n)\n");
		scanf("%c", &a);
	} else
		a = 'Y';
	//if the user says "Y" Then lets get this show on the road!
	if( a == 'Y'){
		printf("\n");
		print_curr_loc();
		print_board();
		printf("Game started, entering infinite loop. Ctrl + C to quit.\n");


		//*********************************************************************
		//GAME LOOP
		//*********************************************************************
		char input[256];
		while(1)
		{

			if(DEBUG){
				printf("Enter a debug command: ");
				scanf("%s", &input);
				int help = strcmp(input, "help");
				int cont = strcmp(input, "continue");
				if(!help){
					printf("HELP: \n\nAdd list of debug commands here\n\n");
				}
				if(!cont){
				}

			}

		//whenever we send position data over bluetooth, we should
		//print it out.
		//whenever we receive data from bluetooth, we should print
		//we will be sending a/ multiple 2D arrays through bluetooth

		//setup gpio's.
		//setup_motors();
		//setup_magnet();


		//setup bluetooth to connect to phone

		//start game
			//check board for initial setup
			//move motors to home
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
		//****************************************************************
		//****************************************************************
	

	}

}


//****************************************************************
//EXTRA FUNCTIONS
//****************************************************************
void print_curr_loc()
{
	printf("Current Location in Steps: X: %d, Y: %d\n", current_x, current_y);
	return;
}

void print_board()
{
	int i = 0;
	int j = 0;
	for(i; i < 8; i++){
		for(j; j < 8; j++){
			printf("%d ", current_board[i][j]);
		}
		printf("\n");
		j = 0;
	}
}

void setup_bluetooth()
{
	printf("\nHere lies logic to set up bluetooth\n");
	printf("This will do I/O with the user for any necessary bluetooth information\n\n");
	return;
}

void check_init()
{
	printf("\nThis function will check the capsense to make sure the board was set up correctly. This won't be able to check that the pieces are in the correct position, but that the 32 pieces are in the 32 spots they should be..\n\n");
}
//******************************************************************
//******************************************************************
