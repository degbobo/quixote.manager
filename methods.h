// needs <stdio.h>
// needs <stdlib.h>

#define MODE_APPEND 'a'
#define MODE_READ 'r'

int string_len(char * contents);
int string_eqv(char * one, char * other);

int fstring_len(FILE * position, char stopper);
char* fstring_build(FILE * position, char stopper);
void fstring_gone(char * string);

FILE* GET_FILE(char mode);
int FCURSOR_FIND(FILE * cursor, char hint);
int FCURSOR_NEXTLINE(FILE * cursor);
