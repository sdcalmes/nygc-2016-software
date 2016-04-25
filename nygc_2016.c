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
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
//A 1 2 3 4 5 6 7 8
//B 1 2 3 4 5 6 7 8
//C 1 2 3 4 5 6 7 8
//D 1 2 3 4 5 6 7 8
//....
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
static int starting_board1[8] = {255, 255, 0, 0, 0, 0, 255, 255};

//the board could also be represented as a string if need be...
char starting_board2[] = "rkbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

int current_board[8][8];
int prev_board[8][8];
int current_x = 0;
int current_y = 0;
int turn = 0; //0 is waiting for phone, 1 is waiting for board.
int packaged_data[8];
//not sure about this one;
char incoming_data[2];
char *parsed_data[2];

void get_board();
void print_curr_loc();
void print_board();
void setup_bluetooth();
void check_init();
void parse_incoming_data();
void move_piece();
void package_board();
int compare_boards();
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
	memcpy(current_board, starting_board, sizeof(int) * 8 * 8);
	memcpy(prev_board, current_board, sizeof(int) * 8 * 8);

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
		printf("Game started, entering infinite loop. Ctrl + C to quit.\n");
		printf("It is the Phone's Turn!\n");
		package_board();
		print_curr_loc();
		print_board();

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
				int move = strcmp(input, "move");
				int motor = strcmp(input, "motor");
				if(!help){
					printf("HELP: \n\n\thelp - show this help screen\n\tcontinue - allows the board do loop through again\n\tmove - move a board piece\n\n");
				}
				if(!move){
					char a[6];
					printf("enter 2 numbers (ex: 10->20): ");
					scanf("%s", a);
					char in[] = "11->21";
					parse_incoming_data(a);
					move_piece();
					turn = 1;
				}
				if(!motor){
					move_steps(100, 100, 1, 1);
					//move_steps(100, 100, 1 ,1);
				}
				if(!cont){
				}

			}


			//poll for changes in capsense, need to keep the board
			//in software so we know which pieces are moved.
			//a 2-d array of booleans should work just fine.

			//compare current capsense with next capsense
			//waiting on the board to move
			if(turn){
				printf("It is the Board's turn!\n");
				if(compare_boards(current_board, prev_board)){
					printf("Boards are the same!\n");
				} else {
					printf("Boards are NOT the same!\n");
					//This means a piece moved!
					memcpy(prev_board, current_board, sizeof(int) * 8 * 8);
					//send board to phone

				}
			} 
			//waiting for return data from bluetooth
			else {
				printf("It is the Phone's turn!\n");

			}


			//wait for response from server with AI/user move
			//parse_incoming_data(DATA_FROM_BLUETOOTH);

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

int compare_boards(int curr[8][8], int prev[8][8]){
	int i = 0;
	int j = 0;
	int diff = 0;
	for(i; i < 8; i++){
		for(j; j < 8; j++){
			if(curr[i][j] != prev[i][j]){
				diff = 1;
				return !diff;
			}
		}
		j = 0;
	}
	return !diff;
}

//get the board from capsense
void get_board(){
}

void parse_incoming_data(char string[]){
	int i = 0;
	printf("incoming string: %s\n", string);
	char *parse = strtok(string, "->");
	while (parse != NULL){
		parsed_data[i++] = parse;
		parse = strtok(NULL, "->");
	}
	printf("\nMove from %s to %s\n\n", parsed_data[0], parsed_data[1]);


	
}

void move_piece(){
	int x1 = parsed_data[0][0] - '0' - 1;
	int y1 = parsed_data[0][1] - '0' - 1;
	int x2 = parsed_data[1][0] - '0' - 1;
	int y2 = parsed_data[1][1] - '0' - 1;

	current_board[x1][y1] = 0;
	current_board[x2][y2] = 1;

	package_board();
	print_curr_loc();
	print_board();
}

void package_board(){
	int i = 0;
	int j = 7;
	int z = 0;
	int package;
	for(i; i < 8; i++){
		package = 0;
		j = 7;
		z = 0;
		for(j; j > -1; j--){
			if(current_board[i][z]){
				package += pow(2,j);
			}
			z++;
		}
		packaged_data[i] = package;
	}
}

void print_curr_loc()
{
	printf("Current Location in Steps: X: %d, Y: %d\n", current_x, current_y);
	return;
}

void print_board()
{
	int i = 0;
	int j = 0;
	int z = 0;
	printf("   1 2 3 4 5 6 7 8\n\n");
	for(i; i < 8; i++){
		printf("%d  ", i + 1);
		for(j; j < 8; j++){
			printf("%d ", current_board[i][j]);
		}
		printf("\n");
		j = 0;
	}
	
	printf("\nPackaged data: ");
	for(z; z < 8; z++){
		printf("%d, ", packaged_data[z]);
	}
	printf("\n");

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
