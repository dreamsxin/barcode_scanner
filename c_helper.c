#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "c_helper.h"

char * trim(char * string){
	char * ptr = string;
	while(isspace(*ptr))
	{
		ptr++;
	}

	char * ptr2;
	ptr2 = string + strlen(string) - 1;
	while(isspace(*ptr2))
	{
		ptr2--;
	}

	int size = ptr2 - ptr + 1 + 1; // +1 for total length of string, +1 for null character
	char * newString = substr(string, ptr - string, ptr2 - string);

	return newString;

}

// return sub string of string from index start to index end
char * substr(char * string, int start, int end){
	char * newString = malloc(end - start + 1 + 1); // get memory for new substring

	int counter = 0; // newString index
	while(start <= end){ // go through sub string
		newString[counter++] = string[start++]; // save sub string into new string
	}
	newString[counter] = '\0'; // put null terminator at end of new string

	return newString; // return
}

// return sub string of string from index(int) start to index(char) end
char * substr_char(char * string, int start, char end)
{
	if(start >= (strlen(string) - 1))
		return NULL; // out of bounds

	char * end_loc = string + start; // new pointer to beginning of string + start offset
	int end_i = strlen(string) - 1; // initialize end location to end of string

	while((end_loc = strchr(end_loc, end))!= NULL)// search for char 'end' in string 'string'
	{
		if(end_loc >= (string + start)) // should always be the case because of end_loc declaration
		{
			end_i = (end_loc - string - 1); // -1 to compensate for found char
			break; // we reached character after start posotion
		}
	}

	return substr(string, start, end_i); // return substring
}


int numChar(char * string, char needle){

	int counter = 0;

	int len = strlen(string);
	int i = 0;
	for(i = 0; i < len; i++){
		if(needle == string[i])
			counter++;
	}

	return counter;
}

struct exploded * explode(char * string, char * delimeter){
	char * ptr = string;
	char * oldptr = string;

	int string_length = strlen(string);

	struct exploded *exploded_ptr = malloc(sizeof(struct exploded)); // first node

	struct exploded *exploded_t = exploded_ptr; // to traverse explode_ptr
	exploded_t->next = 0; // null the next pointer

	while(ptr = strstr(oldptr, delimeter))
	{
		int start = oldptr - string;
		int end = ptr - string - 1;

		// save string, add new node, return pointer to new node
		exploded_t = exploded_add_node(exploded_t, substr(string, start, end));

		ptr = ptr + strlen(delimeter);
		oldptr = ptr;
	}
	
	// copy what's remaining of string to a new node || or if no delimeter exists, this will set the struct to the entire string
	if(oldptr < (string + string_length)) // theres still stuff remaining
	{
		int start = oldptr - string;
		int end = string_length - 1;

		// save string, add new node, return pointer to new node
		exploded_t = exploded_add_node(exploded_t, substr(string, start, end));
	}

	return exploded_ptr;
}

// copy string ot current node->string
// create new node, update nodes pointers
// return address to new node
struct exploded * exploded_add_node(struct exploded * exploded_ptr, char * string){
	exploded_ptr->string = string;
	exploded_ptr->next = malloc(sizeof(struct exploded)); // point to new exploded struct
	exploded_ptr = exploded_ptr->next; // move to this next point
	exploded_ptr->next = 0; // set next to null

	return exploded_ptr;
}

// frees all the nodes in exploded
void free_exploded(struct exploded * head)
{
	struct exploded * tmp;
	while(head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

// returns 1 if string == true, 0 if not
int stringToBool(char * string){
	if(string == NULL)
		return -1;
	
	if(strcasecmp(string, "true") == 0)
		return 1;

	if(strcasecmp(string, "false") == 0)
		return 0;
	else
		return -1;
}



/*
 * Search and replace a string with another string , in a string
 * */
char * str_replace(char *search , char *replace , char *subject)
{
	char  *p = NULL , *old = NULL , *new_subject = NULL ;
	int c = 0 , search_size;
	
	search_size = strlen(search);
	
	//Count how many occurences
	for(p = strstr(subject , search) ; p != NULL ; p = strstr(p + search_size , search))
	{
		c++;
	}
	
	//Final size
	c = ( strlen(replace) - search_size )*c + strlen(subject);
	
	//New subject with new size
	new_subject = malloc( c );
	
	//Set it to blank
	strcpy(new_subject , "");
	
	//The start position
	old = subject;
	
	for(p = strstr(subject , search) ; p != NULL ; p = strstr(p + search_size , search))
	{
		//move ahead and copy some text from original subject , from a certain position
		strncpy(new_subject + strlen(new_subject) , old , p - old);
		
		//move ahead and copy the replacement text
		strcpy(new_subject + strlen(new_subject) , replace);
		
		//The new start position after this search match
		old = p + search_size;
	}
	
	//Copy the part after the last search match
	strcpy(new_subject + strlen(new_subject) , old);
	
	return new_subject;
}
