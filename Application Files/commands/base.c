#define DICTIONARY_FILE "dictionary.txt"

void clear();
void format_output(char*);

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