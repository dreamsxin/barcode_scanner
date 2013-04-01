#ifndef C_HELPER_H_INCLUDED
#define C_HELPER_H_INCLUDED





struct exploded {
	char * string; // pointer to string
	struct exploded *next;
};




char *str_replace(char *search , char *replace , char *subject);

char * trim(char * string); // trims leading and trailing spaces in string

char * substr(char * string, int start, int end); // get sub string from start to end

/* Function: substr_char
 *
 * Purpose: return sub string from desired @start to first occurance of desired @end (after start point)
 *
 * @params: @string - supplied string to search
            @start - integer, point to start from in @string
            @end - character, character to search string for after start
 *
 * Return: char * string - substring from start position to end position
 			NULL on error
 *
 * Note: Caller is responsible for freeing the memory returned from this function
 *
*/
char * substr_char(char * string, int start, char end);



int numChar(char * string, char needle); // search string for needle, return num occurances

struct exploded * explode(char * string, char * delimeter); // explodes string into pieces, setting each piece to a node in struct exploded

struct exploded * exploded_add_node(struct exploded * exploded_ptr, char * string); // assists explode(), adds string to exploded_ptr and returns next node in exploded_ptr

void free_exploded(struct exploded * head);

int stringToBool(char * string); // true == 1, false == 0, neither == -1

#endif