#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

unsigned long long sum = 0;


int checker(char** arr, int size, int wide, int x, int y)
{
	int lval = x-1;
	if(lval<0) lval = 0;
	int rval = x+1;
	if(rval==size) rval = size-1;
	int tval = y-1;
	if(tval<0) tval = 0;
	int bval = y+1;
	if(bval==wide) wide = wide-1;
	printf("start %d, %d. end %d, %d\n", lval, tval, rval, bval);

	int ct = 0;
	for (int i = lval; i<=rval; i++) {
		for(int j = tval;j<=bval; j++) {
			if(i == x && j == y) continue;
			if(*(*(arr+i)+j) == 1) ct++;
		}
	}
	printf("ct: %d\n", ct);
	if(ct > 3) return -1;	
	return 0;
}

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
	char** arr = 0;	
	int size = 0;
	int lenB;
	while(getline(&buf, &uLen, fp) != -1) {
		//length of line
		lenB = strlen(buf);	
		size++;
		arr = realloc(arr, sizeof(char*) * size);
		*(arr+size-1) = calloc(lenB, sizeof(char));
		//printf("line: %d\n", size-1);
		for(int i = 0; i<lenB; i++) {
			if(*(buf+i) == 64) *(*(arr+size-1)+i) = 1;
		}	
	}
	printf("line len%d\n", lenB);
	printf("size %d\n", size);
	for(int i = 0; i<size; i++) {
		for(int j = 0; j<lenB; j++) {
			//printf("%d %d\n", i, j);
			if(checker(arr, size, lenB, i, j) == 0 && *(*(arr+i)+j) == 1){
				printf("added at %d %d\n", i, j);
				sum++;
				}
			}
	}

	printf("sum: %lld\n", sum);
}
