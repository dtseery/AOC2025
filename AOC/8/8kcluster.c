#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

//I Misunderstood the algorithm they want us to create. 
//This algorithm is more efficient and disregards circuits already created
//We need to regard junction boxes as separate entities from circuits
//keeping this code for posterity and knowledge
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

			//printf("points %d & %d, dist:%llu\n", i, j, dist[i][j]);
			//printf("%llu\n", dist[i][j]);
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
				//skips unused
				if(j <= k) continue;
				//skips empty buckets
				if(*(bucketSize+j) == -1 || *(bucketSize+k) == -1) continue;
				if(dist[j][k] < min) {
					min = dist[j][k];
					min1 = j;
					min2 = k;
				}
				/*if(j == 19) {
					printf("dist of 19 to %d is %llu\n", k, dist[19][k]);
				}*/	
			}
		}
		printf("merging: %d and %d with minimum of %llu\n", min1, min2, min);
		printf("bucket size: %d and %d\n", *(bucketSize+min1), *(bucketSize+min2));
		if(min == -1 || min1 == -1 || min2 == -1) {
			printf("error min could not be found!\n");
			return -1;
		}

		//fact is bucket A will always be a higher index than bucket B

		//increment bucket A by size of bucket B
		*(bucketSize+min1)+=*(bucketSize+min2);
		//buckets merged so bucket A is garbage and set to -1
		*(bucketSize+min2) = -1;
		//replace old minimum, so that next minimum can find new minimum
		dist[min1][min2] = -1;
		//update values of k as minimum between bucket A and B

		//printf("replacements;\n");	
		//loop replaces all comparisons between min2 and data
		for(int j = 0; j<dataSize; j++) {
			//don't check when the current cell is compared
			if(j == min1 || j == min2) continue;
			//case that j is greater than min2, no flips
			if(j < min2 && dist[min2][j] < dist[min1][j]) {
				//printf("%llu at %d,%d for %llu\n at %d,%d\n", dist[min2][j], min2, j, dist[min1][j], min1, j);
				dist[min1][j] = dist[min2][j];
				continue;
			}
			if(j < min2) continue;
			//case that j is greater than min2, but not min1, 1 flip
			if(j < min1 && dist[j][min2] < dist[min1][j]) {
				//printf("%llu at %d,%d for %llu\n at %d,%d\n", dist[j][min2], j, min2, dist[min1][j], min1, j);
				dist[min1][j] = dist[j][min2];
				continue;
			}
			if(j < min1) continue;
			//case greater than both, both flip
			if(dist[j][min2] < dist[j][min1]) {
				//printf("%llu at %d,%d for %llu\n at %d,%d\n", dist[j][min2], j, min2, dist[j][min1], j, min1);
				dist[j][min1] = dist[j][min2];
			}
			
		}
		//set values at bucket B to inf so its never selected
		for(int k = 0; k<dataSize; k++) {
			if(k<min2) dist[min2][k] = -1;
			else if(k>min2) dist[k][min2] = -1;
		}

	}
	for(int i = 0; i<dataSize; i++) {
		printf("bucket %d, has amount %d\n", i, *(bucketSize+i));
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
