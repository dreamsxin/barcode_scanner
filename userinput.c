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
	printf("\n->");
	fgets(line, sizeof(line), stdin);
}

void printMainMenu(){
	char * Menu[10][100]; // declare array, max string length 99 characters + \0 (null)

	// store menu items in string array
	Menu[0][0] = " 1. Add New Ingredient into Pantry";
	Menu[1][0] = " 2. Add New Ingredient into Freezer";
	Menu[2][0] = " 3. Add New Ingredient into Fridge";
	Menu[3][0] = " 4. Move Ingredient From Pantry to Freezer";
	Menu[4][0] = " 5. Move Ingredient From Pantry to Fridge";
	Menu[5][0] = " 6. Move Ingredient From Freezer to Pantry";
	Menu[6][0] = " 7. Move Ingredient From Freezer to Fridge";
	Menu[7][0] = " 8. Move Ingredient From Fridge to Pantry";
	Menu[8][0] = " 9. Move Ingredient From Fridge to Freezer";
	Menu[9][0] = "10. ";

	// display menu
	int menu_count = 10;
	int i = 0;
	for(i = 0; i < menu_count; i++){
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