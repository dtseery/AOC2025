#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>

//We Must use this range method
//expected workflow
//
//array finds all ranges that overlap
//combines that shit
//dynamically corrects the size of our corresponding arrays
//a recursive approach may prove helpful

unsigned long long sum = 0;

int main(int argc, char** argv) {
	FILE* fp = NULL;
	//buffer & len for input
	fp = fopen(*(argv+1), "r");
	if (fp == NULL) {
		printf("Error opening file. Make sure file exists.\\n");
		return -1; // Exit the program with an error
	}
	//get line params
	char* buf = NULL;
	size_t uLen = 0;

	//arrays for values
	unsigned long long* lRange = 0;
	unsigned long long* rRange = 0;
	//array to designate population
	unsigned int* populated = 0;
	unsigned long long size = 0;
	char* DELIM = "-";	
	//loop to get ranges
	while(getline(&buf, &uLen, fp) != -1 && *buf != '\n') {
		//tokenized left and right values
		char* tok1 = strtok(buf, DELIM);
		char* tok2 = strtok(NULL, DELIM);
		//printf("%s %s\n", tok1, tok2);

		//turning tokens into longs
		unsigned long long valL = strtoll(tok1, NULL, 10);
		unsigned long long valR = strtoll(tok2, NULL, 10);
		//printf("L%lld R%lld \n", valL, valR);
		//value for first overlap if needed
		int fOvr = -1; 
		//variables to hold overlap array
		int sizeOfOverlap = 0;
		int* overlapArr = 0;
		//setting left and right values of maxL and maxR
		unsigned long long maxL = valL;
		unsigned long long maxR = valR;	

		//loop to find overlaps and add idx to array
		for(int i = 0; i<size; i++) {
			//check if valid overlap
			if(populated[i] == 0) continue;
			//checks that range does not touch the current range
			if(valL > rRange[i]+1) continue;
			if(valR < lRange[i]-1) continue;

			sizeOfOverlap++;
			overlapArr = realloc(overlapArr, sizeof(int) * sizeOfOverlap);
			overlapArr[sizeOfOverlap-1] = i;
			if(lRange[i] < maxL) maxL = lRange[i];
			if(rRange[i] > maxR) maxR = rRange[i];		
		}

		//in the case of no overlap
		if(sizeOfOverlap == 0) {
			int f = -1;
			for(int i = 0; i<size; i++) { 
				//find first unpopulated cell, otherwise -1 to signal creation of new cell
				if(populated[i] == 0) {
					f = i;
					break;
				}	
			}
			if(f == -1) {
				//if no empty space due to a previous overlap, we increment the size of the array
				size++;
				lRange = realloc(lRange, sizeof(unsigned long long) * size);
				rRange = realloc(rRange, sizeof(unsigned long long) * size);
				populated = realloc(populated, sizeof(unsigned int) * size);
				lRange[size-1] = valL;
				rRange[size-1] = valR;
				populated[size-1] = 1;	
			} else {
				//in the case of an empty spaced caused by overlap
				//we want to consolidate that space so we reassign it	
				lRange[f] = valL;
				rRange[f] = valR;
				populated[f] = 1;					
			}
		} else {
			//overlapArr[0] is index to replace!
			lRange[overlapArr[0]] = maxL;
			rRange[overlapArr[0]] = maxR;
			//check if more than one overlap and mark them
			if(sizeOfOverlap>1) {
				for(int i = 1; i<sizeOfOverlap; i++) {
					populated[overlapArr[i]] = 0;
				}
			}
		}	
	}

	//loop to get sum
	for(int i = 0; i<size; i++) {
		//if the array is properly populated, add range values to sum
		//printf("%d %lld %lld\n", populated[i], rRange[i], lRange[i]);
		if(populated[i] == 1) sum += (rRange[i]-lRange[i]+1);
	}
	printf("sum: %lld\n", sum);
}
