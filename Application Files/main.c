#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary_base.h"

int main(int argc, char* argv[]) {
	if (argc > 1)
		analyze_arguments(argc,argv);
}

/**
 * Analyzes the arguments provided after the command to see what to do
 *
 *  -a, --add
 * 		add an entry to the dictionary
 * 	-l, --list
 * 		list all of the entries that begin with specified characters
 * 	-o, --organize
 * 		organize all entries stored
 * 	-d, --define
 * 		prints the entry of a specified word
 * 	-c, --clear
 * 		clears the current dictionary file
 * 	-r, --remove
 * 		removes a specific entry from the dictionary file
 * 		
 * @param count Count of arguments provided
 * @param value Value of arguments provided
 */
void analyze_arguments(int count, char* value[]) {
	// Allocates space for the argument needing to be checked
	char* arg = malloc(sizeof(char)*strlen(value[1]));

	// Copies the argument to the memory allocated for it
	strcpy(arg,value[1]);

	// Checks the argument
	if (!strcmp(arg,"-a") || !strcmp(arg,"--add"))
		// Add a definition to the dictionary
		add_entry();
	else if (!strcmp(arg,"-l") || !strcmp(arg,"--list"))
		// List all entries
		list_entry(count,value);
	else if (!strcmp(arg,"-c") || !strcmp(arg,"--clear"))
		// Clears the dictionary file
		clear();

	// Frees up memory allocated
	free(arg);
}