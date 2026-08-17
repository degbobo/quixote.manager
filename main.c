#include <stdio.h>
#include <stdlib.h>
#include <methods.h>
#include <direct.h>
#include <windows.h>

#include WRITE_KEYWORD "summon"

#define FILE_PATH "C:\\Users\\duren\\projs\\Proj_Manager\\quixote_logs"

// Writes to quixote_logs -> project_name;project_directory
// entries sperated by a ';'
void file_write(char * proj_name, char * directory) {
	FILE * file;
	file = GET_FILE(MODE_APPEND);

	int index = 0;
	while (proj_name[index] != '\0') {
		fprintf(file, "%c", directory[index]);
		index++;
	}
	fprintf(file, ";");
	index = 0;
	while (directory[index] != '\0') {
		fprintf(file, "%c", directory[index]);
		index++;
	}
	fprintf(file, "\n");
	fclose(file);
}

// lets me search quixote_logs by project name
// returns the directory path of the project
char* file_search_name(char * proj_name) {
	FILE * file;
	file = GET_FILE(MODE_READ);
	char* read;
NAME_READ:
	read = fstring_build(file, ';');	// read a string from the file
	int ret = string_eqv(read, proj_name); 	// compare the new string to the desired project name
	fstring_gone(read);
	if (ret == 0) {
		int end_of_file = FCURSOR_NEXTLINE(file);
		if (end_of_file == -1) return nullptr; // if we're at the end of the file, it's because there's no such name -> return nullptr
		goto NAME_READ;
	}

	FCURSOR_FIND(file, ';');
	read = fstring_build(file, '\n');
	fclose(file);
	return read;
}

// search projects by order of entry
// returns the directory path of the project
char* file_search_option(int option) {
	FILE* file;
	file = GET_FILE(MODE_READ);
	for (int i = 1; i < option; i++) {
		int ret = FCURSOR_NEXTLINE(file);
		if (ret == -1) return nullptr;
	}
	FCURSOR_FIND(file, ';');
	char * read = fstring_build(file, '\n'); // when correct option is found, it builds the string and returns it
	fclose(file);
	return read;
}


