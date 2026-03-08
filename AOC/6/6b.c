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
	int lenB;
	//one deref for rows, one for string containing each num
	char** strIn = NULL;
	int* strSize = NULL;
	//array for operations
	char* op = NULL;
	while(getline(&buf, &uLen, fp) != -1) {
		//length of line
		if(strlen(buf) > lenB) lenB = strlen(buf);
		//printf("size of curr buf: %d\n", lenB);
		char* tok;
		tok = strtok(buf, DELIM);
		//generate strSize array based on line size
		//strSize represents size+null terminator
		if(strSize == NULL) strSize = calloc(lenB, sizeof(int));
		//we know that the str will be a consistent number of lines
		if(strIn == NULL) strIn = calloc(lenB, sizeof(char*));
		//check if number is the start of the line -> line of num input
		if(*tok > 43) {
			//we don't need to allocate for a new string each line, just have the
			//possibility to add to each string in the size of line
			for(int i = 0; i<lenB; i++) {
				//if a point is empty in the line we continue
				if(*(buf+i) == ' ') continue;
				//if its not empty, but null, we need to create a new string at that location
				if(*(strIn+i) == NULL) { 
					//allocation of first character and null terminator of new string
					*(strSize+i)+=2;	
					*(strIn+i) = malloc(*(strSize+i)*sizeof(char));	
					**(strIn+i) = *(buf+i);
					*(*(strIn+i)+1) = '\0';
					//increment string size
				} else {
					//if we already allocate, inc size, and resize string
					//then concat character
					*(strSize+i)+=1;
					*(strIn+i) = realloc(*(strIn+i),*(strSize+i) * sizeof(char));
					strncat(*(strIn+i), (buf+i), 1 * sizeof(char));
				}

			}	
			continue;
		}
		//loop for operations
		op = calloc(sizeof(unsigned int), lenB);
		for(int i = 0; tok != NULL; i++) {
			*(op+i) = *tok;	
			tok = strtok(NULL, DELIM);
		}
	}
	int ic = 0;
	for(int pc = 0; pc<lenB; pc++) {
		unsigned long long rv;
		if(*(op+ic) == 42) {
			rv = 1;	
			while(*(strSize+pc) != 0 && **(strIn+pc) != '\0') {
				printf("val of %s with size %d at pc %d\n", *(strIn+pc), *(strSize+pc), pc);
				char* tok2 = strtok(*(strIn+pc), DELIM);
				if(tok2 == NULL) break;
				rv *= strtoll(*(strIn+pc), NULL, 10);
				pc++;
			}
			ic++;
		} else {
			rv = 0;
			while(*(strSize+pc) != 0) {
				printf("val of %s with size %d at pc %d\n", *(strIn+pc), *(strSize+pc), pc);
				char* tok2 = strtok(*(strIn+pc), DELIM);
				if(tok2 == NULL) break;
				rv += strtoll(*(strIn+pc), NULL, 10);
				pc++;
			}
			ic++;
		}
		printf("val added: %lld curr pc %d\n", rv, pc);
		sum+=rv;	
	}
	printf("%lld\n", sum);

}
