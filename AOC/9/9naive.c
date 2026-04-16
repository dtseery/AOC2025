#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

unsigned long long sum = 0;
char* DELIM = ",";

typedef struct {
	unsigned long long x;
	unsigned long long y;
} Point;

int main(int argc, char** argv) {
	FILE* fp = NULL;
	//buffer & len for input
	fp = fopen(*(argv+1), "r");
	if (fp == NULL) {
		printf("Error opening file. Make sure file exists.\\n");
		return -1; // Exit the program with an error
	}

	//array for 4 considerable points
	int coMax[4];

	//array for 2 actual points
	int max[2];

	//array for all points
	Point* arr = 0;
	int dataSize = 0;

	char* buf = NULL;
	size_t uLen = 0;
	while(getline(&buf, &uLen, fp) != -1) {
		//length of line
		int lenB = strlen(buf);
		dataSize++;		
		arr = realloc(arr, dataSize*sizeof(Point));
		(arr+dataSize-1)->x = strtol(strtok(buf, DELIM), NULL, 10);	
		(arr+dataSize-1)->y = strtol(strtok(NULL, DELIM), NULL, 10);	
		if(dataSize < 2) continue;
		if(dataSize == 2) {
			max[0] = 0;
			max[1] = 1;
			sum = (abs(arr[max[0]].x - arr[max[1]].x)+1) * (abs(arr[max[0]].y - arr[max[1]].y)+1); 
			continue;
		}
		if(dataSize == 3){
			//check new point against maxes
			for(int i = 0; i<2; i++) {
				unsigned long long val = (abs(arr[max[i]].x - arr[dataSize-1].x)+1) 
					* (abs(arr[max[i]].y - arr[dataSize-1].y)+1); 
				if(val > sum) {
					max[0] = max[i];
					max[1] = dataSize-1;
					sum = val;
				}
			}
			continue;
		}
		if(dataSize == 4) {	
			coMax[0] = 0;
			coMax[1] = 1;
			coMax[2] = 2;
			coMax[3] = 3;
			//check new point against maxes
			for(int i = 0; i<dataSize-1; i++) {
				unsigned long long val = (abs(arr[i].x - arr[dataSize-1].x)+1) 
					* (abs(arr[i].y - arr[dataSize-1].y)+1); 
				if(val > sum) {
					max[0] = i;
					max[1] = dataSize-1;
					sum = val;
					printf("ds4max is now %d point %lld,%lld and %d point %lld, %lld\n", max[0], arr[max[0]].x, arr[max[0]].y,max[1], arr[max[1]].x, arr[max[1]].y);
				}
			}

		}
		if(dataSize < 5) continue;
		//check new point against coMaxes
		int valEquals = 0;
		unsigned long long pointMin = -1;
		int minPoint = -1;
		for(int i = 0; i<4; i++) {
				unsigned long long diff1 = abs(arr[coMax[i]].x - arr[dataSize-1].x) + 1;
				unsigned long long diff2 = abs(arr[coMax[i]].y - arr[dataSize-1].y) + 1;
				unsigned long long val = diff1*diff2;
				//printf("cal runs %llu * %llu to become -> %llu\n", diff1, diff2, val);
				if(val > sum) {
					max[0] = coMax[i];
					max[1] = dataSize-1;
					printf("max is now %d point %lld,%lld and %d point %lld, %lld\n", max[0], arr[max[0]].x, arr[max[0]].y,max[1], arr[max[1]].x, arr[max[1]].y);
					sum = val;
					printf("sum is %llu\n", sum);
				}
				if(val == sum) valEquals = 1;
				if(val < pointMin) {
					pointMin = val;
					minPoint = i;
				}
		}
		//replace point that is the closest to the new point
		//if the new point is in the max
		if(max[1] == dataSize-1 || (max[1] != dataSize-1 && valEquals)) {
			printf("replacing coMax:%d, at %d point %lld, %lld, with new %d point %lld, %lld\n", minPoint, coMax[minPoint], arr[coMax[minPoint]].x, arr[coMax[minPoint]].y, dataSize-1, arr[dataSize-1].x, arr[dataSize-1].y);
			coMax[minPoint] = dataSize-1;
		}

	}

	printf("ending area is %llu\n", sum);
}
