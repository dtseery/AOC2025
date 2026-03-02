#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

unsigned long long sum = 0;
char* DELIM = " ";

int main(int argc, char** argv) {
	FILE* fp = NULL;
	//buffer & len for input
	fp = fopen(*(argv+1), "r");
	if (fp == NULL) {
		printf("Error opening file. Make sure file exists.\\n");
		return -1; // Exit the program with an error
	}
	char* buf = NULL;
	size_t uLen = 0;
	
	//one deref for rows, one for numbers in row, one for size of each num
	char*** strIn;
	//array for vals
	unsigned int** vals;
	//number of vals counter
	int sVals = 0;
	//array for operations
	char* op;
	while(getline(&buf, &uLen, fp) != -1) {
		//length of line
		int lenB = strlen(buf);
		//printf("size of curr buf: %d\n", lenB);
				
		
		//loop for operations
		op = calloc(sizeof(unsigned int), lenB);
		for(int i = 0; tok != NULL; i++) {
			*(op+i) = *tok;	
			tok = strtok(NULL, DELIM);
		}
	}
	for(int pc = 0; *(*(vals)+pc); pc++) {
		printf("st: %d\n", *(*(vals)+pc));
		unsigned long long rv;
		if(*(op+pc) == 42) {
			rv = 1;	
			for(int i = 0; i<sVals; i++) {
				//printf("blah1\n");	
				rv *= *(*(vals+i)+pc);
				//printf("loc %d curr val %lld\n", pc, rv);
			}
		} else {
			rv = 0;
			for(int i = 0; i<sVals; i++) {
				//printf("blah\n");
				rv += *(*(vals+i)+pc);
				//printf("loc %d curr val %lld\n", pc, rv);
			}
		}
		sum+=rv;	
	}
	printf("%lld\n", sum);

}
