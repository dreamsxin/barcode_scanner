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

int insert_upc_pantry();
int insert_upc_freezer();
int insert_upc_fridge();

void clrscr(); // clears terminal screen

//char *replacestr(char *string, char *sub, char *replace);

//void saveResultsToStruct(struct barcode_information * barcode_info_p, struct exploded * head);





int main(void)
{
	clrscr(); // clear screen

	printf("Hello Ronald and Kara\n");
	printf("Welcome to the Recipe Management Barcode Scanner shiznit\n");
	printf("Please select what you would like to do:\n");


	while(1) // continually ask user for activity 
	{
		printMainMenu();
		int choice = parse_user_input_activity(); // take user input, and convert to int
		switch(choice){
			case 1:
				insert_upc_pantry();
			break;

			case 2:
				insert_upc_freezer();
			break; 

			case 3:
				insert_upc_fridge();
			break;

			default:
				clrscr();
				printf("Please enter a valid input:\n");
				printMainMenu();
			break;
		}
		clrscr();
	}

	return 0;
}


int insert_upc_freezer()
{
	// keep asking for barcodes
	while(ask_for_barcode() == 0){

		//allocate memory for struct
		struct barcode_information *barcode_info_p = malloc(sizeof(struct barcode_information));
	
		barcode_info_p->status = 0; // initialize status

		strncpy(barcode_info_p->upc, line, sizeof(barcode_info_p->upc) - 1); // save barcode into struct

		char * results  = scan_barcode(barcode_info_p->upc);
		printf("Results: \n %s\n", results);

		struct exploded * resultsE = explode(results, "\n"); // split results from new line character
		print_exploded(resultsE);

		if(test_scan_results(barcode_info_p, resultsE) == 0){
			printf("Scan Failed, barcode not found\n");
			continue; // go to next scan request
		}
		printf("scan passed, barcode found\n");	

		char * insert_results = insert_update_freezer_from_upcid(barcode_info_p->upcid);

		if(stringToBool(insert_results) != -1){
			printf("Scan Failed on insert\n");
			continue;
		}

		print_struct_barcode(barcode_info_p);

		free(barcode_info_p); // free allocated memory

		memset(line, 0, sizeof(line));
	}

	return 0;
}

int insert_upc_fridge()
{
	// keep asking for barcodes
	while(ask_for_barcode() == 0){

		//allocate memory for struct
		struct barcode_information *barcode_info_p = malloc(sizeof(struct barcode_information));
	
		barcode_info_p->status = 0; // initialize status

		strncpy(barcode_info_p->upc, line, sizeof(barcode_info_p->upc) - 1); // save barcode into struct

		char * results  = scan_barcode(barcode_info_p->upc);
		printf("Results: \n %s\n", results);

		struct exploded * resultsE = explode(results, "\n"); // split results from new line character
		print_exploded(resultsE);

		if(test_scan_results(barcode_info_p, resultsE) == 0){
			printf("Scan Failed, barcode not found\n");
			continue; // go to next scan request
		}
		printf("scan passed, barcode found\n");	

		char * insert_results = insert_update_fridge_from_upcid(barcode_info_p->upcid);

		if(stringToBool(insert_results) != -1){
			printf("Scan Failed on insert\n");
			continue;
		}

		print_struct_barcode(barcode_info_p);

		free(barcode_info_p); // free allocated memory

		memset(line, 0, sizeof(line));
	}

	return 0;
}



int insert_upc_pantry()
{
	// keep asking for barcodes
	while(ask_for_barcode() == 0){

		//allocate memory for struct
		//struct barcode_information *barcode_info_p = malloc(sizeof(struct barcode_information));
		struct barcode_information *barcode_info_p = calloc(1, sizeof(struct barcode_information));
		if(barcode_info_p == NULL)
		{
			printf("Failed to calloc()\n");
			continue;
		}
	
		barcode_info_p->status = 0; // initialize status

		strncpy(barcode_info_p->upc, line, sizeof(barcode_info_p->upc) - 1); // save barcode into struct

		char * results  = scan_barcode(barcode_info_p->upc);
		/*
		//char * results  = "TRUE\n12345";
		printf("Results: \n %s\n", results);
		*/
		struct exploded * resultsE = explode(results, "\n"); // split results from new line character
		print_exploded(resultsE);

		if(test_scan_results(barcode_info_p, resultsE) == 0){
			printf("Scan Failed, barcode not found\n");
			continue; // go to next scan request
		}
		printf("scan passed, barcode found\n");	
		

		//char * insert_results = insert_update_pantry_from_upcid(barcode_info_p->upcid);
		char * insert_results = "piid";

		if(stringToBool(insert_results) != -1){
			printf("Scan Failed on insert\n");
			continue;
		}

		print_struct_barcode(barcode_info_p);

		free(barcode_info_p); // free allocated memory

		memset(line, 0, sizeof(line));
	}

	return 0;
}

void clrscr(){
	system("clear");
}
