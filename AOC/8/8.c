#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

unsigned long long sum = 1;
char* DELIM = ",";

typedef struct {
	unsigned int x;
	unsigned int y;
	unsigned int z;
} Point;

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
	Point* arr = 0;
	int dataSize = 0;
	//store input in points	
	while(getline(&buf, &uLen, fp) != -1) {
		//length of line
		int lenB = strlen(buf);
		dataSize++;
		arr = realloc(arr, dataSize*sizeof(Point));
		(arr+dataSize-1)->x = strtol(strtok(buf, DELIM), NULL, 10);	
		(arr+dataSize-1)->y = strtol(strtok(NULL, DELIM), NULL, 10);	
		(arr+dataSize-1)->z = strtol(strtok(NULL, DELIM), NULL, 10);	
		//printf("%d %d %d in\n", (arr+dataSize-1)->x, (arr+dataSize-1)->y, (arr+dataSize-1)->z);
	}
	//buckets correspond to sets of points, this may be needed for future steps
	//Point** buckets = calloc(dataSize, sizeof(Point*));
	
	//array buckets do not need numbers, but we need to know how big they are
	int* bucketSize = malloc(dataSize * sizeof(int));
	//populate initial buckets of size 1
	for(int i = 0; i<dataSize; i++) {
		*(bucketSize+i) = 1;
	}
	
	//array of euc distances between points
	//long long may be needed for no overflow when doing x-x squared
	unsigned long long dist[dataSize][dataSize];
	//populate array with euc distances
	for(int i = 0; i<dataSize; i++) {
		for(int j = 0; j<dataSize; j++) {
			//only populate needed squares
			//when j > i
			if(i <= j) continue;
			int dx = (arr+i)->x - (arr+j)->x;
			int dy = (arr+i)->y - (arr+j)->y;
			int dz = (arr+i)->z - (arr+j)->z;


			dist[i][j] += (dx*dx);
			dist[i][j] += (dy*dy);
			dist[i][j] += (dz*dz);

			//printf("points %d & %d, dist: %lld\n", i, j, dist[i][j]);
		}
	}
	//find shortest euc distance n times
	int n = 10;
	for(int i = 0; i<n; i++) {
		//find minimum
		unsigned long long min = -1;
		int min1 = -1;
		int min2 = -1;
		for(int j = 0; j<dataSize; j++) {
			for(int k = 0; k<dataSize; k++) {
				if(j <= k) continue;
				if(dist[j][k] < min) {
					min = dist[j][k];
					min1 = j;
					min2 = k;
				}	
			}
		}

		if(min == -1 || min1 == -1 || min2 == -1) {
			printf("error min could not be found!\n");
			return -1;
		}

		//fact is bucket A will always be a higher index than bucket B

		//increment bucket B by size of bucket A
		*(bucketSize+min2)+=*(bucketSize+min1);
		//buckets merged so bucket A is garbage and set to -1
		*(bucketSize+min1) = -1;

		//update values of k as minimum between bucket A and B
		//loop ends at bucket A index to avoid garbage comparison	
		for(int j = 0; j<min1; j++) {
			//compares distances between merging rows
			//merging row min1 with min2 checks corresponding distances
			if(dist[min1][j] < dist[min2][j]) dist[min2][j] = dist[min1][j];
		}

		//set values at bucket a to 0
		for(int k = 0; k<min1; k++) {
			dist[min1][k] = -1;
		}

	}
	for(int i = 0; i<3; i++) {
		int mx = -1;
		int mI = -1;
		for(int j = 0; j < dataSize; j++) {
			if(*(bucketSize+j) > mx) {
				mx = *(bucketSize+j);
				mI = j;
			}
		}
		printf("mx%d: %d\n", i, mx);	
		sum *= mx;
		*(bucketSize+mI) = -1;	
	}
	printf("end val: %lld\n", sum);
}
