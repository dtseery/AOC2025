#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>


//THIS IS MY ORIGINAL APPROACH TO PART 2
//IT IS CORRECT IN COMPUTATION, BUT DOES NOT ACCOUNT
//FOR MEMORY & DATA LIMITATIONS
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
	unsigned long long* vals = NULL;
	unsigned long long maxSize = 0;
	char* DELIM = "-";	
	//loop to get ranges
	printf("preloop\n");		
	while(getline(&buf, &uLen, fp) != -1 && *buf != '\n') {
		char* tok1 = strtok(buf, DELIM);
		char* tok2 = strtok(NULL, DELIM);
		//printf("%s %s\n", tok1, tok2);
		unsigned long long lRange = strtoll(tok1, NULL, 10);
		unsigned long long rRange = strtoll(tok2, NULL, 10);
		if(rRange > maxSize) {
			vals = realloc(vals, sizeof(unsigned long long) * (rRange+1));
			if(maxSize > 0) 
			{
				memset((vals+maxSize+1), 0, (rRange-maxSize)*sizeof(unsigned long long)); 	
			for(unsigned long long i = 0; i<= maxSize; i++) {
				printf("%lld %lld\n", i, vals[i]);
			}
			}
			else memset(vals, 0, sizeof(unsigned long long) * rRange);
			printf("%lld %lld\n", maxSize+1, rRange-maxSize);
			maxSize = rRange;
		}
		for(unsigned long long i = lRange; i<=rRange; i++) {
			//printf("%lld %lld\n", vals[i], i);
			vals[i]++;
			//printf("%lld %lld\n", vals[i], i);
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

	//loop to get all values
	for(unsigned long long i = 0; i<=maxSize; i++) {
		if(vals[i] > 0) {
		printf("%lld %lld\n", i, vals[i]);
			sum++;
		}
	}
	printf("sum: %lld\n", sum);
}
