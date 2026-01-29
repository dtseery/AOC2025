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
	while(getline(&buf, &uLen, fp) != -1) {
		lRange = realloc(lRange, size*sizeof(unsigned long long));
		rRange = realloc(lRange, size*sizeof(unsigned long long));

	}
	printf("sum: %lld\n", sum);
}
