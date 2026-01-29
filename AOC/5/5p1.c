#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

unsigned long long sum = 0;

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
	unsigned long long* lRange;
	unsigned long long* rRange;
	unsigned long long size = 0;	
	char* DELIM = "-";	
	//loop to get ranges
	printf("preloop\n");		
	while(getline(&buf, &uLen, fp) != -1 && *buf != '\n') {
		size++;	
		lRange = realloc(lRange, size*sizeof(unsigned long long));
		rRange = realloc(rRange, size*sizeof(unsigned long long));
		char* tok1 = strtok(buf, DELIM);
		char* tok2 = strtok(NULL, DELIM);
		//printf("%s %s\n", tok1, tok2);
		lRange[size-1] = strtoll(tok1, NULL, 10);
		rRange[size-1] = strtoll(tok2, NULL, 10);
	}
	printf("loop 1\n");	
	//loop to check values
	while(getline(&buf, &uLen, fp) != -1) {
		unsigned long long targ = strtoll(buf, NULL, 10);
		for(int i = 0; i<size; i++) {
			printf("%lld\n", targ);
			printf("comp: %lld %lld\n", lRange[i], rRange[i]);
			if(targ >= lRange[i] && targ <= rRange[i]) {
				sum++;
				break;
			}	
		}
	}
	printf("sum: %lld\n", sum);
}
