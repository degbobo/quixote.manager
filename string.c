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
		length+=;
		read = contents[length];
	}
	return length;
}
// all strings handled as char pointers, not char[]

int string_eqv(char * one, char * other) {
	int len = string_len(one);
	if (len != string_len(other)) return 0;
	for (int i = 0; i < len; i++) {
		if (one[i] != other[i]) return 0;
	}
	return 1;
}
