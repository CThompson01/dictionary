void add_entry();
void write_entry(char*,char*);

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