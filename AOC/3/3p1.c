#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

unsigned int sum = 0;

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
		char largDigits[3];
		memset(largDigits, 0, 3);
		int largIdx[2] = {0,0};
		//loop cannot find last digit as will always be smaller
		for(int i = 0; i<lenB-2; i++) {
			//current digit
			int curr = buf[i]- '0';
			printf("1curr%d %c\n", curr, largDigits[0]);
			if(curr > (largDigits[0]-'0')) {
				largDigits[0] = buf[i];
				largIdx[0] = i;
			}	
		}
		//loop to find largest digit in seq
		for(int i = largIdx[0]+1; i<lenB-1; i++) {	
			int curr = buf[i]- '0';
			printf("2curr%d i%d %c\n", curr, i, largDigits[1]);
			if(curr > (largDigits[1]-'0')) {
				largDigits[1] = buf[i];
				largIdx[1] = i;
			}	
		}
		printf("val: %s\n", largDigits);
		sum+=atoi(largDigits);
		
	}
	printf("sum: %d\n", sum);
}
