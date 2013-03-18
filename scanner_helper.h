#ifndef SCANNER_HELPER_H_INCLUDED
#define SCANNER_HELPER_H_INCLUDED

// struct to hold all information for a given UPC
struct barcode_information{
	char title[100];
	char description[1000];
	char upc[100];
	char upcid[100];
	char nutrition[1000];
	char calories[50];
	char amount[10];
	char qtid[100];
	char qtype[100];
	int status;
};

extern struct exploded * head;



/* Function: print_exploded
 *
 * Purpose: print each node of @head line by line
 *
 * @params: @exploded * head
 *
 * Return: 
 *
 * Note: 
 *
*/
void print_exploded(struct exploded * head);




/* Function: print_struct_barcode
 *
 * Purpose: Print to screen what is contained in supplied @barcode_info_p
 *
 * @params: @barcode_info_p
 *
 * Return: 
 *
 * Note: 
 *
*/
void print_struct_barcode(struct barcode_information * barcode_info_p);




/* Function: saveResultsToStruct
 *
 * Purpose: save exploded results into @barcode_info_p structure
 *
 * @params: @barcode_info_p - pointer to barcode_information struct
 *          @*head - pointer to linked list of exploded values
 *
 * Return: 
 *
 * Note: 
 *
*/
void saveResultsToStruct(struct barcode_information * barcode_info_p, struct exploded * head);



/* Function: getBitFromInt
 *
 * Purpose: return bit value in the interger @num specified by @bitnum
 *
 * @params: @num - number to get bit from
 *          @bitnum - bit location in @num to get
 *
 * Return: int bit (0 or 1)
 *
 * Note: 
 *
*/
int getBitFromInt(int num, int bitnum);


/* Function: test_scan_results
 *
 * Purpose: verifies exploded[0] == TRUE and exploded[1] has upcid
 *
 * @params: @barcode_info_p - pointer to struct
 *          @exploded *head - pointer to exploded string
 *
 * Return: 1 on pass, 0 on fail
 *
 * Note: 
 *
*/
int test_scan_results(struct barcode_information * barcode_info_p, struct exploded * head);

#endif