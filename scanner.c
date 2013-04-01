#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "pantry_api.h"
#include "c_helper.h"
#include "scanner_helper.h"

extern struct barcode_information * barcode_info_ptr;

extern struct exploded * exploded_ptr;

extern char line[100];

int insert_upc_pantry(struct barcode_information *barcode_info_p);
int insert_upc_freezer(struct barcode_information *barcode_info_p);
int insert_upc_fridge(struct barcode_information *barcode_info_p);
int reset_barcode(struct barcode_information *barcode_info_p);
struct exploded * scan_barcode(struct barcode_information *barcode_info_p);


void clrscr(); // clears terminal screen

//char *replacestr(char *string, char *sub, char *replace);

//void saveResultsToStruct(struct barcode_information * barcode_info_p, struct exploded * head);


int main(void)
{
	clrscr(); // clear screen

	printf("Hello Ronald and Kara\n");
	printf("Welcome to the Recipe Management Barcode Scanner shiznit\n");
	printf("Please select what you would like to do:\n");

	struct barcode_information *barcode_info_p = malloc(sizeof(struct barcode_information));
	if(barcode_info_p == NULL)
	{
		printf("Failed to allocate memory for barcode information. Exiting");
		exit(0);
	}

	while(1) // continually ask user for activity 
	{
		printMainMenu();
		
		int choice = parse_user_input_activity(); // take user input, and convert to int
		switch(choice)
		{
			case 1:
				insert_upc_pantry(barcode_info_p);
			break;

			case 2:
				insert_upc_freezer(barcode_info_p);
			break; 

			case 3:
				insert_upc_fridge(barcode_info_p);
			break;

			default:
				clrscr();
				printf("Please enter a valid input:\n");
				printMainMenu();
			break;
		}

		clrscr();

	}

	free(barcode_info_p); // free allocated memory from barcode_information struct

	return 0;
}




int insert_upc_pantry(struct barcode_information *barcode_info_p)
{
	// keep asking for barcodes
	while(ask_for_barcode() == 0){ // line[100] == user input

		reset_barcode(barcode_info_p);

		struct exploded * resultsE = scan_barcode(barcode_info_p);

		if(resultsE == NULL)
		{
			printf("barcode scan failed at pantry\n");
			continue;
		}

		print_exploded(resultsE);

		if(test_scan_results(barcode_info_p, resultsE) == 0){ // verify result is TRUE and upcid exists
			printf("Scan Failed, barcode not found\n");
			continue; // go to next scan request
		} else {
			printf("scan passed, barcode found\n");	
		}

		char * insert_results = insert_update_pantry_from_upcid(barcode_info_p->upcid);
		char * true_false = insert_results; // clone results into true/false to be parsed

		// this gets the string up to the first newline character
		// shouyld be TRUE/FALSE
		char * newline = strchr(insert_results, '\n');
		if(newline != NULL) // if NULL, newline doesn't exist
		{
			true_false = substr(insert_results, 0, newline - insert_results);
			true_false = trim(true_false);	
		}
		

		if(stringToBool(true_false) == -1){
			printf("Scan neither failed or passed. Something else happened\n");
			printf("insert results: %s\n", insert_results);
			//#DEBUG:
			//saveLog();
			continue;
		}
		else
			printf("insert results: %s\n", insert_results);

		
		print_struct_barcode(barcode_info_p);

		free(insert_results); // free allocated memory from cURL call

		free_exploded(resultsE); // free allocated memory from explode() function

		memset(line, 0, sizeof(line));
	}

	return 0;
}


int insert_upc_freezer(struct barcode_information *barcode_info_p)
{
	// keep asking for barcodes
	while(ask_for_barcode() == 0){

		reset_barcode(barcode_info_p);

		struct exploded * resultsE = scan_barcode(barcode_info_p);

		if(resultsE == NULL)
		{
			printf("barcode scan failed at freezer\n");
			continue;
		}

		print_exploded(resultsE);

		if(test_scan_results(barcode_info_p, resultsE) == 0) // verify result is TRUE and upcid exists
		{
			printf("Scan Failed, barcode not found\n");
			continue; // go to next scan request
		} else {
			printf("scan passed, barcode found\n");	
		}

		char * insert_results = insert_update_freezer_from_upcid(barcode_info_p->upcid);
		char * true_false = insert_results; // clone results into true/false to be parsed

		// this gets the string up to the first newline character
		// shouyld be TRUE/FALSE
		char * newline = strchr(insert_results, '\n');
		if(newline != NULL) // if NULL, newline doesn't exist
		{
			true_false = substr(insert_results, 0, newline - insert_results);
			true_false = trim(true_false);	
		}
		

		if(stringToBool(true_false) == -1){
			printf("Scan neither failed or passed. Something else happened\n");
			printf("insert results: %s\n", insert_results);
			//#DEBUG:
			//saveLog();
			continue;
		}
		else
			printf("insert results: %s\n", insert_results);

		
		print_struct_barcode(barcode_info_p);

		free(insert_results); // free allocated memory from cURL call

		free_exploded(resultsE); // free allocated memory from explode() function

		memset(line, 0, sizeof(line));
	}

	return 0;
}

int insert_upc_fridge(struct barcode_information *barcode_info_p)
{
	// keep asking for barcodes
	while(ask_for_barcode() == 0){

		reset_barcode(barcode_info_p);

		struct exploded * resultsE = scan_barcode(barcode_info_p);
		if(resultsE == NULL)
		{
			printf("barcode scan failed at fridge\n");
			continue;
		}
		
		print_exploded(resultsE);

		if(test_scan_results(barcode_info_p, resultsE) == 0) // verify result is TRUE and upcid exists
		{
			printf("Scan Failed, barcode not found\n");
			continue; // go to next scan request
		} else {
			printf("scan passed, barcode found\n");	
		}	

		char * insert_results = insert_update_fridge_from_upcid(barcode_info_p->upcid);
		
		// this gets the string up to the first newline character
		// shouyld be TRUE/FALSE
		char * true_false = substr_char(insert_results, 0, '\n');		

		if(stringToBool(true_false) == -1){
			printf("Scan neither failed or passed. Something else happened\n");
			printf("insert results: %s\n", insert_results);
			//#DEBUG:
			//saveLog();
			continue;
		}
		else
			printf("insert results: %s\n", insert_results);


		print_struct_barcode(barcode_info_p);

		free(insert_results); // free allocated memory from cURL call

		free_exploded(resultsE); // free allocated memory from explode() function

		memset(line, 0, sizeof(line));
	}

	return 0;
}

int reset_barcode(struct barcode_information *barcode_info_p)
{
	memset(barcode_info_p, 0, sizeof(struct barcode_information)); // set barcode_info_p to all 0's to remove any phantom data in memory
	
	barcode_info_p->status = 0; // initialize status

	strncpy(barcode_info_p->upc, line, sizeof(barcode_info_p->upc) - 1); // save barcode into struct

	return 0;
}

struct exploded * scan_barcode(struct barcode_information *barcode_info_p)
{
	char * scan_results = api_scan_barcode(barcode_info_p->upc); // call website with upc
	if(scan_results == NULL){
		printf("reuslts failed\n");
		return NULL;
	} else {
		printf("results: %s\n", scan_results);
	}
		

	struct exploded * resultsE = explode(scan_results, "\n"); // split results from new line character

	free(scan_results);

	return resultsE;
}



void clrscr(){
	system("clear");
}
