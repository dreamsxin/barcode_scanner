#include <stdio.h>
#include <string.h>
#include "c_helper.h"
#include "scanner_helper.h"



void print_exploded(struct exploded * head)
{
	struct exploded * head2 = head;
	while(head2->next != 0)
	{
		printf("String: %s\n", head2->string);
		head2 = head2->next;
	}
}


void print_struct_barcode(struct barcode_information * barcode_info_p)
{
	printf("Barcode info: title = %s\n", barcode_info_p->title);
	printf("Barcode info: description = %s\n", barcode_info_p->description);
	printf("Barcode info: upc = %s\n", barcode_info_p->upc);
	printf("Barcode info: upcid = %s\n", barcode_info_p->upcid);
	printf("Barcode info: nutrition = %s\n", barcode_info_p->nutrition);
	printf("Barcode info: calories = %s\n", barcode_info_p->calories);
	printf("Barcode info: amount = %s\n", barcode_info_p->amount);
	printf("Barcode info: qtid = %s\n", barcode_info_p->qtid);
	printf("Barcode info: qtype = %s\n", barcode_info_p->qtype);
	printf("Barcode info: status = %i\n", barcode_info_p->status);
}


void saveResultsToStruct(struct barcode_information * barcode_info_p, struct exploded * head)
{
	int counter = 0;
	while(head->next != NULL)
	{
		char * value = head->string;
		head = head->next;

		switch(counter++)
		{
			case 0: // barcodeFound
				barcode_info_p->status += 0x1*stringToBool(trim(value));
			break;

			case 1: // barcodeComplete
				barcode_info_p->status += 0x2*stringToBool(trim(value));
			break;

			case 2: // upcid
				strncpy(barcode_info_p->title, trim(value), 100);
			break;

			case 3: //title
				strncpy(barcode_info_p->upcid, trim(value), 100);
			break;

			case 4: // description
				strncpy(barcode_info_p->description, trim(value), 1000);
			break;

			case 5: // qtid
				strncpy(barcode_info_p->qtid, trim(value), 100);
			break; 

			case 6:// qtype
				strncpy(barcode_info_p->qtype, trim(value), 100);
			break;

			case 7: // amount
				strncpy(barcode_info_p->amount, trim(value), 10);
			break;

			case 8: // calories
				strncpy(barcode_info_p->calories, trim(value), 50);
			break;

			case 9: // nutrition
				strncpy(barcode_info_p->nutrition, trim(value), 1000);
			break;
		}
	}

	printf("status: %d\n", barcode_info_p->status);
}

int getBitFromInt(int num, int bitnum){
	return (num & ( 1 << bitnum )) >> bitnum;
}


int test_scan_results(struct barcode_information * barcode_info_p, struct exploded * head)
{
	char * status;
	if(head->next != 0) {
		status = head->string;
	} else {
		printf("nothing in head\n");
		return 0; // nothing in head
	}

	if(stringToBool(status) != 1)
	{
		printf("head[0] != TRUE \n");
		return 0; // head[0] != TRUE
	}

	head = head->next; // next head, should be upcid

	if(stringToBool(head->string) != -1) // verify head[1]->string != TRUE || FALSE
	{
		printf("head[1] == TRUE || head[1] == FALSE\n");
		return 0;
	}

	strncpy(barcode_info_p->upcid, head->string, sizeof(barcode_info_p->upcid) - 1); // save upcid

	return 1;
}