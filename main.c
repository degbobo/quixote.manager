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
