#include <stdio.h>
#include <stdlib.h>
#include "methods.h"
#include <direct.h>
#include <windows.h>

// i wanna characterize the project a bit more
#define WRITE_KEYWORD "summon"
#define CLEAN_KEYWORD "clean"
#define PEEK_KEYWORD "peek"

// Writes to quixote_logs -> project_name;project_directory
// entries sperated by a ';'
void file_write(char * proj_name, char * directory) {
	FILE * file;
	file = GET_FILE(MODE_APPEND);

	int index = 0;
	while (proj_name[index] != '\0') {
		fprintf(file, "%c", proj_name[index]);
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

// method to display all of the projects
// changes to the visual/logic are made here
// return 0 -> success
// return -1 -> no such file / empty file
int display_projects() {
	FILE * file;
	file = GET_FILE(MODE_READ);
	if (fgetc(file) == EOF) return -1;
	fseek(file, -1, SEEK_CUR);
	printf(":: QUIXOTE ::\n");
	int end_of_file = 1;
	int count = 1;
	while (end_of_file != -1) {
		char * line_name = fstring_build(file, ';');
		if (line_name == nullptr) break;
		printf("%d. %s\n", count, line_name);

		count++;
		fstring_gone(line_name);
		end_of_file = FCURSOR_NEXTLINE(file);
	}
	return 0;
}

// the method/logic behind spawning a new instance/going to project directory
// return 0 -> success
// return -1 -> fail
int QUIXOTE_METHOD(char * directory) {
	printf("...tell 'Dulcinea De Dulcinea of my deeds!\n", directory);

	// windows.h code; to start new process
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	char command[] = "C:\\Program Files\\Git\\git-bash.exe"; // creating a new instance of git-bash
	
	BOOL success = CreateProcess(
		NULL,
		command,
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		directory,
		&si,
		&pi
	);

	if (!success) return -1;
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}

// a mess of if statements !!
int main(int argc, char * argv[]) {
	char current_dir[1024];
	if (_getcwd(current_dir, sizeof(current_dir)) == NULL) return 0;
	
	if (argc == 3) { // if "quixote arg1 arg2"
		if (string_eqv(argv[1], WRITE_KEYWORD) == 1) { // if program is called with the correct keyword!
			file_write(argv[2], current_dir); // writes "project_name;C:\current\directory" to quixote_log
			printf("... and Don Quixote imagined...\n");
		}
		else {
			printf("No such keyword \"%s\"\n", argv[1]);
			return 0;
		}
	}
	else if(argc == 2) { //if "quixote arg1"
		if (string_eqv(argv[1], CLEAN_KEYWORD) == 1) {
			// THEN DELETE THE FILE
			remove(FILE_PATH);   // allegedlly the syntax to delete a file
			return 0;
		}
		else if (string_eqv(argv[1], PEEK_KEYWORD) == 1) {
			//then ONLY print the project list
			display_projects();
			return 0;
		}
		// then we search quixote_logs using file_search_name, under name: arg1
		char * wished_directory = file_search_name(argv[1]);
		if (wished_directory == nullptr) goto CASE_2_END; //if no such project exist, then...
		QUIXOTE_METHOD(wished_directory);
CASE_2_END:
		free(wished_directory);
		return 0;
	}

	// if argc != 2 or 3, then just default to display
	int value = display_projects();
	if (value == -1) goto CASE_3_END;
	printf("q exit\n");

	int input = getchar();
	if (input == 'Q' || input == 'q') return 0; 
	// if anything but q is pressed, try to search for it in quixote_logs
	// search by option
	char * wished_directory = file_search_option(input - 48);
	if (wished_directory == nullptr) goto CASE_3_END; // if option doesnt exist then...
	QUIXOTE_METHOD(wished_directory);
CASE_3_END:
	free(wished_directory);

	return 0;
}
