#ifndef PANTRY_API_H_INCLUDED
#define PANTRY_API_H_INCLUDED
/* ^^ these are the include guards */



struct MemoryStruct {
  char *memory;
  size_t size;
};

extern struct barcode_information *barcode_p;

//int populateCompleteBarcode(struct barcode_information *barcode_p);

//char * addUpcPantry(char upcid[100]);
//char * addUpcFreezer(char upcid[100]);

/*
*/



/* Function: insert_update_freezer_from_upcid
 *
 * Purpose: insert or update pantry freezer item by @upcid
 *
 * @params: @upcid = scanned barcode
 *
 * Return: "TRUE" on success
 *         "FALSE" on error
 *
 * Note: should pull qtype/amount from matching ingredients table, not upcIngredients table
 *
*/
char * insert_update_freezer_from_upcid(char upcid[100]);



/* Function: insert_update_fridge_from_upcid
 *
 * Purpose: insert or update pantry fridge item by @upcid
 *
 * @params: @upcid = scanned barcode
 *
 * Return: "TRUE" on success
 *         "FALSE" on error
 *
 * Note: should pull qtype/amount from matching ingredients table, not upcIngredients table
 *
*/
char * insert_update_fridge_from_upcid(char upcid[100]);



/* Function: insert_update_pantry_from_upcide
 *
 * Purpose: insert or update pantry pantry item by @upcid
 *
 * @params: @upcid = scanned barcode
 *
 * Return: "TRUE" on success
 *         "FALSE" on error
 *
 * Note: should pull qtype/amount from matching ingredients table, not upcIngredients table
 *
*/
char * insert_update_pantry_from_upcid(char upcid[100]);



/* Function: scan_barcode
 *
 * Purpose: get barcode information from supplied @barcode
 *
 * @params: @barcode = scanned barcode
 *
 * Return: @barcode_info - notifies caller if barcode data complete and 
 *
 * Note: 
 *
*/
char * api_scan_barcode(char barcode[100]); // calls api to lookup supplied barcode




/* Function: get_iid_from_upcid
 *
 * Purpose: Get IID from supplied @upcid
 *
 * @params: @upcid = scanned barcode
 *
 * Return: iid from upcIngredients table
 *         or "FALSE" on error
 *
 * Note: 
 *
*/
char * get_iid_from_upcid(char upcid[100]);



/* Function: get_piid_from_iid
 *
 * Purpose: return pantry piid in relation to supplied @iid
 *
 * @params: @iid = ingredients iid
 *
 * Return: piid on success
 *         "FALSE" on error
 *
 * Note:
 *
*/
char * get_piid_from_iid(char iid[100]);




/* Function: get_iid_information
 *
 * Purpose: Get information in regards to supplied @iid
 *
 * @params: @iid = ingredients IID
 *
 * Return: qtid\n
 		   qtype\n
 		   ingredient
 *
 * Note: 
 *
*/
char * get_iid_information(char * iid);




/* Function: get_upcid_information
 *
 * Purpose: Get information in regards to supplied @upcid
 *
 * @params: @upcid = scanned barcode
 *
 * Return: title\n
 		   description\n
 		   qtid\n
 		   qtype\n
 		   amount\n
 		   calories\n
 		   nutrition\n
 *
 * Note: 
 *
*/
char * get_upcid_information(char * upcid);


/* Function: get_qtid_from_iid
 *
 * Purpose: returns qtid from supplied @iid
 *
 * @params: @iid - ingredients ID
 *
 * Return: @qtid
 *
 * Note: 
 *
*/
char * get_qtid_from_iid(char * iid);




/* Function: get_qtid_from_upcid
 *
 * Purpose: returns qtid from supplied @upcid
 *
 * @params: @upcid - ingredients ID
 *
 * Return: @qtid
 *
 * Note: 
 *
*/
char * get_qtid_from_upcid(char * upcid);


/* Function: get_qtid_from_qtype
 *
 * Purpose: returns qtid from supplied @qtype
 *
 * @params: @qtype - name of quantity type
 *
 * Return: @qtid
 *
 * Note: 
 *
*/
char * get_qtid_from_qtype(char * qtype);


/* Function: get_qtypes
 *
 * Purpose: returns all known qtypes, tab delimited for easy viewing in terminal
 *
 * @params: @
 *
 * Return: prints out qtypes tab delimited
 *
 * Note: 
 *
*/
char * get_qtypes();



/* Function: get_default_qtids
 *
 * Purpose: returns all the possible qtids for iid from @upcid from defaultQuantities table
 *
 * @params: @upcid - barcode
 *
 * Return: @dqids
 *
 * Note: 
 *
*/
char * get_default_qtids(char * upcid);




/* Function: move_upc_location
 *
 * Purpose: move @upcid by amount from @from to @to
 *
 * @params: @upcid = scanned barcode
 *          @amount = amount to be moved
 *          @from = from locatoin (fridge, freezer, pantry)
 *          @to = to location (fridge, freezer, pantry)
 *
 * Return: "FALSE" on error
 *         "TRUE\n<PIID>" on pass
 *
 * Note: User must specify appropriate @from and @to fields.
 *		 Valid @from/@to: "freezer" "fridge" "pantry"
 *
*/
char * move_upc_location(char upcid[100], char * amount, char * from, char * to);



/* Function: increase_upc_location
 *
 * Purpose: Increase @upcid by @amount at @location
 *
 * @params: @upcid = scanned barcode
 *          @amount = amount to be increased by
 *          @location = Location to increase amount by to
 *
 * Return: "FALSE" on error
 *         "TRUE" on success
 *
 * Note: User must specify appropriate @location field
 *       Valid @location: "freezer" "fridge" "pantry"
 *
*/
char * increase_upc_location(char upcid[100], char * amount, char * location);



/* Function: decrease_upc_location
 *
 * Purpose: Decrease @upcid by @amount at @location
 *
 * @params: @upcid = scanned barcode
 *          @amount = amount to be increased by
 *          @location = Location to increase amount by to
 *
 * Return: "FALSE" on error
 *         "TRUE" on success
 *
 * Note: User must specify appropriate @location field
 *       Valid @location: "freezer" "fridge" "pantry"
 *
*/
char * decrease_upc_location(char upcid[100], char * amount, char * location);








// returns html from supplied @url
char * getURLData(char *url);
// helper function for getURLData
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);


#endif