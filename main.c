#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DICTIONARY_FILE "dictionary.txt"

void add_entry();
void write_entry(char*,char*);
void analyze_arguments(int,char*[]);

int main(int argc, char* argv[]) {
	if (argc > 1)
		analyze_arguments(argc,argv);
}

/**
 * Goes through the process of getting the word and definition
 * Passes the word and definition to the file writer
 */
void add_entry() {
	// Intialize variables for the word title and definition
	char* title = (char*) malloc(sizeof(int) * 50);
	char* definition = (char*) malloc(sizeof(int) * 200);

	// Get the input for the word title
	printf("ENTER WORD >> ");
	scanf("%[^\n]%*c",title);

	// Get the input for the word definition
	printf("ENTER DEFINITION >> ");
	scanf("%[^\n]%*c",definition);

	// Reallocate memory because efficiency
	title = (char*) realloc(title,sizeof(int)*strlen(title));
	definition = (char*) realloc(definition,sizeof(int)*strlen(definition));

	// Write the entry input
	write_entry(title,definition);

	// Free memory up
	free(title);
	free(definition);
}

/**
 * Appends an entry to the dictionary file
 *
 * Format of appended words is
 * word@definition
 * 
 * @param title      The title of the word (the word)
 * @param definition The definition of the word
 */
void write_entry(char* title, char* definition) {
	// Initializes the file to be appended to
	FILE* file_printer = fopen(DICTIONARY_FILE,"a");

	// Writes the word and definition to the file in word@definition format
	fprintf(file_printer, "%s@%s\n",title,definition);

	// Closes the file
	fclose(file_printer);
}

/**
 * Formats the output of the word and definition
 * @param buff The buffer storing the current word and definition combo
 */
void format_output(char* buff) {
	// Prints the first letter of the word as a capital
	printf("%c",toupper(buff[0]));

	// Iterates through the rest of the definition
	for (int i = 1; i < strlen(buff); i++) {
		// If the current character is '@' then begin definition line
		if (buff[i] != '@')
			printf("%c",buff[i]);
		else
			printf("\n    ");
	}
}

/**
 * Lists all entries that begin with the letter specified
 * If no letter is specified then all entries will be printed out
 * @param count The amount of arguments provided from initial command call
 * @param value The value of arguments from the initial command call
 */
void list_entry(int count, char* value[]) {
	// Initialize the file to be read
	FILE* file_reader = fopen(DICTIONARY_FILE,"r");

	// If a letter is unspecified list all entries
	// If a letter is specified only list those entries
	char list = '?';
	if (count>2)
		list = value[2][0];

	// Set up buffers to iterate through every entry in the file
	char* curr_buff = malloc(sizeof(char)*255);
	char* prev_buff = malloc(sizeof(char)*255);
	fgets(curr_buff, 255, file_reader);

	// Iterate through the file until the previous buffer is the same as current buffer
	while (curr_buff != NULL && strcmp(prev_buff,curr_buff)) {
		// Checks if the first letter of the current buffer is the correct letter
		if (curr_buff[0] == list || list == '?')
			format_output(curr_buff);

		// Moves the current buffer to the previous buffer
		strcpy(prev_buff,curr_buff);

		// Updates the current buffer
		fgets(curr_buff, 255, file_reader);
	}

	// Free memory up
	free(curr_buff);
	free(prev_buff);

	// Closes the file
	fclose(file_reader);
}

void clear() {
	// Initializes the confirmation variable
	char confirmation = 'N';

	// Checks for confirmation to clear all entries
	printf("Are you sure you want to clear all entries?\nEnter 'Y' to confirm >> ");
	scanf("%c",&confirmation);

	// If confirmed clear the entries
	if (confirmation == 'Y') {
		// Initialize the file to be cleared
		FILE* file_writer = fopen(DICTIONARY_FILE,"w");
		// Clear the file
		fprintf(file_writer,"");
		// Close the file
		fclose(file_writer);
	}
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