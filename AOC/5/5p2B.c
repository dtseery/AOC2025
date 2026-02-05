#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>

//Theoretically an implementation which keeps track of ranges could work.
//But it is a lot of work.

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
	while(getline(&buf, &uLen, fp) != -1 && *buf != '\n') {
		char* tok1 = strtok(buf, DELIM);
		char* tok2 = strtok(NULL, DELIM);
		//printf("%s %s\n", tok1, tok2);
		unsigned long long valL = strtoll(tok1, NULL, 10);
		unsigned long long valR = strtoll(tok2, NULL, 10);
		int overlap = 0;
		
		for(int i = 0; i<size; i++) {
			//checks that range does not touch the current range
			if(valL > rRange[i]+1) continue;
			if(valR < lRange[i]-1) continue;

			//in the case that the ranges touch, it updates the current range
			if(valL < lRange[i]) lRange[i] = valL;
			if(valR > rRange[i]) rRange[i] = valR;
			
			//loop to check new range against each other
			for(int j = 0; j<size; j++) {
				
			}
			//set to 1 to indicate overlap, so no adding the range
			overlap = 1;
			break;
		}

		if(overlap == 0) {
			size++;
			lRange = realloc(lRange, sizeof(unsigned long long) * size);
			rRange = realloc(rRange, sizeof(unsigned long long) * size);
			lRange[size-1] = valL;
			rRange[size-1] = valR;	
		}	
	}
	/*printf("loop 1\n");	
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
	}*/

	//loop to get sum
	for(int i = 0; i<size; i++) {
		for(unsigned long long j = lRange[i]; j<=rRange[i]; j++) {
			printf("val: %lld\n", j);
			sum++;
		}
	}
	printf("sum: %lld\n", sum);
}
