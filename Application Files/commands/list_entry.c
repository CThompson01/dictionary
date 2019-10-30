void list_entry(int,char*[]);

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