#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>

//This code would also, work, although it may take a long time
//ranges for the real test are herculean
//we must resort to a dynamic approach

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
	char** vals = NULL;
	int size = 0;
	char* DELIM = "-";	
	//loop to get ranges
	printf("preloop\n");		
	while(getline(&buf, &uLen, fp) != -1 && *buf != '\n') {
		char* tok1 = strtok(buf, DELIM);
		char* tok2 = strtok(NULL, DELIM);
		//printf("%s %s\n", tok1, tok2);
		unsigned long long lRange = strtoll(tok1, NULL, 10);
		unsigned long long rRange = strtoll(tok2, NULL, 10);
		for(unsigned long long i = lRange; i<=rRange; i++) {
			char curr[strlen(tok2)+1];
			//putting string into buffer
			snprintf(curr, sizeof(curr), "%lld", i);
			//loop to find current value in our list
			int found = 0;
			for(int j = 0; j<size; j++) {
				if(strcmp(curr, *(vals+j)) == 0) {
					found = 1;
					break;
				}
			}
			//if found we do not do anything
			if(found == 1) {
			 	continue;
			}

			//if not found we add it
			size++;
			vals = realloc(vals, sizeof(char*) * size);
			*(vals+size-1) = malloc(strlen(curr) * sizeof(char));
			strncpy(*(vals+size-1), curr, strlen(curr));	

			printf("added %s\n", curr);		
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

	printf("sum: %d\n", size);
}
