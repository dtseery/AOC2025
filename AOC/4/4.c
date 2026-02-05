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
	while(getline(&buf, &uLen, fp) != -1) {
		//length of line
		int lenB = strlen(buf);
		//largest info
		char largDigits[13];
		memset(largDigits, 0, 13*sizeof(char));
		int largIdx[12];
		memset(largIdx, 0, 12*sizeof(int));
		//SLIDING WINDOW ALGORITHM LOOP
		//IDX of end offset
		int DIGIDX = 12;
		//IDX of start index
		int nsIdx = 0;

		//loop to find 12 values
		for(int i = 0; i<12; i++) {
			for(int j = nsIdx; j<lenB-DIGIDX; j++) {	
				//current digit
				int curr = buf[j]- '0';
				//printf("1curr%d %c\n", curr, largDigits[0]);
				//compare largest in current i idx to current
				if(curr > (largDigits[i]-'0')) {
					largDigits[i] = buf[j];
					largIdx[i] = j;
				}	
			}
			//determine next start index from prev
			nsIdx=largIdx[12-DIGIDX]+1;
			//increase size of ending index for full search
			DIGIDX--;
		}

		printf("val: %s\n", largDigits);
		sum+=strtoll(largDigits, NULL, 10);

	}
	printf("sum: %lld\n", sum);
}
