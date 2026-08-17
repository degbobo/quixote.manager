#include <stdio.h>
#include <stdlib.h>

// could use #include <string.h>
// but I wanted to practice writing myself

// function to get the length of null-terminated string
// doesn't account for null-terminate character
int string_len(char * contents) {
	int length = 0;
	char read = contents[0];
	while (read != '\0') {
		length++;
		read = contents[length];
	}
	return length;
}
// all strings handled as char pointers, not char[]

// Is string one equivalent to string other?
// return 0 -> false
// return 1 -> true
int string_eqv(char * one, char * other) {
	int len = string_len(one);
	for (int i = 0; i < len; i++) {
		if (one[i] != other[i]) return 0;
	}
	return 1;
}

// FILE STRINGS

// returns the length from the file cursor to a specific character
int fstring_len(FILE * position, char stopper) {
	int bookmark = ftell(position); // saves position of the cursor
	int length = 0;
	char read = fgetc(position); // reads a character; moves cursor forward one
	while (read != stopper && read != EOF && read != NULL) {
		length++;
		read = fgetc(position);
	}
	fseek(position, bookmark, SEEK_SET); //resets cursor/file pointer
	return length;
}

// builds a string from the file cursor and stops at a specific character
char* fstring_build(FILE * position, char stopper) {
	int bookmark = ftell(position);
	int len = fstring_len(position, stopper);
	if (len == 0) return nullptr); // then there is no string to build!
	
	char * string = malloc(len + 1);
	char read = fgetc(position);
	int index = 0;
	while (read != stopper && read != EOF && read != NULL) { // filling the allocated memory with file contents
		string[index] = read;
		read = fgetc(position); // get next
		index++;
	}
	string[len] = '\0';
	fseek(position, bookmark, SEEK_SET);
	return string;
}

// for naming convention
char* fstring_gone(char * string) {
	free(string);
}


