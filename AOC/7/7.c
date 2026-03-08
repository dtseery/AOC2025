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
	int lenB = 0;
	char* currArr = 0;
	while(getline(&buf, &uLen, fp) != -1) {
		//length of line
		if(strlen(buf) > lenB)lenB = strlen(buf);
		//printf("here\n");
		char* newArr = calloc(lenB, sizeof(char));
		//printf("here2\n");
		for(int i = 0; i<lenB; i++) {
			//printf("currArr %s\n", buf);
			//check if first line
			if(currArr == NULL) {
				if(*(buf+i) == 'S') {
				//printf("here4\n");
				*(newArr+i) = 'S';
				}
				continue;
			}
			//if not first line, then check for a split between curr line and next line
			if(*(buf+i) == '^' && *(currArr+i) == 'S') {
			//printf("here5\n");
				*(newArr+i-1) = 'S';
				*(newArr+i+1) = 'S';
				sum+=1;
				continue;	
			}
			//if no split, check if last line had a line
			if(*(currArr+i) == 'S') *(newArr+i) = 'S';	
		}
		//set curr line to next line
		currArr = newArr;
	}
	printf("sum: %lld\n", sum);
}
