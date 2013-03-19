#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "userinput.h"
#include "c_helper.h"

char line[100];

// ask user to enter barcode
int ask_for_barcode(){
	printf("Please enter the barcode: "); // prompt user
	get_input(); // save input
	if(line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = 0; // remove new line

	//char * replaced = str_replace(" ", "%20", line);
	//strncpy(line, replaced, sizeof(line) - 1); // turn spaces into encoded, %20
	//free(replaced); // free memory allocated from str_replace

	if(strcmp(line, "exit") == 0){
		return -1; // user wants out of loop
	}
	else
		return 0; // valid input
}


void get_input(){
	fgets(line, sizeof(line), stdin);
}

void printMainMenu(){
	char * Menu[6][100]; // declare array, max string length 99 characters + \0 (null)

	// store menu items in string array
	Menu[0][0] = "1. Add Ingredient new to Pantry";
	Menu[1][0] = "2. Add Ingredient to Freezer";
	Menu[2][0] = "3. Add Ingredient to Fridge";

	// display menu
	int i = 0;
	for(i = 0; i < 3; i++){
		printf("%s \n", Menu[i][0]);
	}
}

// where the magic happens
// iteratively poll for user input
int parse_user_input_activity()
{
	int choice = -1;
	// get user input
	get_input();

	// calculate length of user input
	int lengthUserInput = strlen(line)-1;

	// if it's length is 1, then we might have a number
	if(lengthUserInput == 1){

		choice = atoi(line); // convert intput to a number
		return choice; // return input

	} else{ // input too long, definitely wrong

		return -1; // bad input

	}
}