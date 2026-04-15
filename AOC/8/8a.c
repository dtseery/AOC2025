#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <gmp.h>

unsigned long long sum = 1;
char* DELIM = ",";

typedef struct {
	unsigned int x;
	unsigned int y;
	unsigned int z;
	int group;
} Point;

/*typedef struct {
  Point a;
  Point b;
  unsigned long long dist;
  } Connection;
  */ 
//number of points is only 1000, if extremely large (10000+) 
//min heap will be the best structure for identifying connections


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
		(arr+dataSize-1)->group = dataSize;
		//printf("%d %d %d in\n", (arr+dataSize-1)->x, (arr+dataSize-1)->y, (arr+dataSize-1)->z);
	}
	printf("done with input\n");	
	
	//array of euc distances between points
	//long long may be needed for no overflow when doing x-x squared
	mpz_t **dist = malloc(dataSize*sizeof(mpz_t*));
	for(int i = 0; i<dataSize; i++) {
		*(dist+i) = malloc(dataSize*sizeof(mpz_t));
	}
	//populate array with euc distances
	for(int i = 0; i<dataSize; i++) {
		for(int j = 0; j<dataSize; j++) {
			//only populate needed squares
			//when j > i
			if(i <= j) continue;
			int dx = (arr+i)->x - (arr+j)->x;
			int dy = (arr+i)->y - (arr+j)->y;
			int dz = (arr+i)->z - (arr+j)->z;
			
			mpz_t sdx, sdy, sdz;
			mpz_init(sdx);
			mpz_init(sdy);
			mpz_init(sdz);
			char dxs[32]; 
			char dys[32];
			char dzs[32];
			snprintf(dxs, sizeof(dxs), "%d", dx);
			snprintf(dys, sizeof(dys), "%d", dy);
			snprintf(dzs, sizeof(dzs), "%d", dz);

			mpz_init_set_str(sdx, dxs, 10);	
			mpz_init_set_str(sdy, dys, 10);	
			mpz_init_set_str(sdz, dzs, 10);
			mpz_mul(sdx, sdx, sdx);	
			mpz_mul(sdy, sdy, sdy);	
			mpz_mul(sdz, sdz, sdz);	

			mpz_init(dist[i][j]);
			mpz_add(dist[i][j], dist[i][j], sdx);
			mpz_add(dist[i][j], dist[i][j], sdy);
			mpz_add(dist[i][j], dist[i][j], sdz);
			//printf("points %d & %d, dist:%llu\n", i, j, dist[i][j]);
			mpz_clear(sdx);
			mpz_clear(sdy);
			mpz_clear(sdz);
			gmp_printf("%Zd\n", dist[i][j]);
		}
	}
	//find shortest euc distance n times
	int n = 1000;
	for(int i = 0; i<n; i++) {
		//find minimum
		//
		//forced to use large numbers for comparison because of overflow	
		mpz_t min;
		mpz_init(min);
		mpz_set_str(min, "184467440737095516150000", 10);
		int min1 = -1;
		int min2 = -1;
		for(int j = 0; j<dataSize; j++) {
			for(int k = 0; k<dataSize; k++) {
				//skips unused
				if(j <= k) continue;
				//if(dist[j][k] < min) {
				
				if(mpz_cmp(dist[j][k], min) < 0) {
					mpz_set(min, dist[j][k]);
					min1 = j;
					min2 = k;
				}
				/*if(j == 19) {
					printf("dist of 19 to %d is %llu\n", k, dist[19][k]);
				}*/	
			}
		}
		gmp_printf("merging: %d and %d with minimum of %Zd\n", min1, min2, min);
		if(min1 == -1 || min2 == -1) {
			printf("error min could not be found!\n");
			return -1;
		}

		//firstly, in every case we set the dist to -1 so it cannot be found again
		mpz_set_str(dist[min1][min2], "184467440737095516150000", 10);

		//if both points are in the same network, we do not need to change anything
		if(arr[min1].group == arr[min2].group) continue;
		
		int newG = arr[min1].group;
		int oldG = arr[min2].group;
		//printf("NEW GROUP %d\n", newG);
		//in this case we need to merge the two groups of points
		//first put all points of min2 group in min1 group
		for(int j = 0; j<dataSize; j++) {
			if(arr[j].group == oldG) {
				arr[j].group = newG;
				//printf("replaced value at %d\n", j);
			}
		}
		
		//loop autoreplaces oldG in min2
		
		for(int j = 0; j<dataSize; j++) {
			//printf("new values P%d: %d\n", j, arr[j].group);
		}
	}
	//create array for totals 
	unsigned long totals[dataSize];
	memset(totals, 0, sizeof(unsigned long) * dataSize);
	for(int i = 0; i<dataSize; i++) {
		//printf("added 1 to %d\n", arr[i].group-1);
		totals[arr[i].group-1]+=1;
	}

	for(int i = 0; i<3; i++) {
		unsigned long max = 0;
		int ej = 0;
		for(int j = 0; j<dataSize; j++) {
			if(totals[j] > max) {
				max = totals[j];
				ej = j;
			}
		}
		printf("end val %d: %ld\n", ej, totals[ej]);
		sum *= totals[ej];
		totals[ej] = 0;
	}	


	printf("end val: %lld\n", sum);
}
