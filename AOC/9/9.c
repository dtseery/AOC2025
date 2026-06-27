#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

unsigned long long sum = 0;
char* DELIM = ",";
int finalhullsize = 0;

typedef struct {
	unsigned long long x;
	unsigned long long y;
} Point;

int pointCompare (const void* pA, const void* pB) 
{
    int x1 = ((Point*)pA)->x;
    int x2 = ((Point*)pB)->x;
    int y1 = ((Point*)pA)->y;
    int y2 = ((Point*)pB)->y;
    if (x1 > x2) return 1;
    if (x2 < x1) return -1;
    if (y1 > y2) return 1;
    if (y2 < y1) return -1;
    return 0;
}
unsigned long long dist(Point a, Point b) {
	return abs((long long)(a.x-b.x)) * abs((long long)(a.y-b.y));
};

unsigned long long absArea (Point a, Point b, Point c) {
	return abs((a.x * b.y + b.x * c.y + c.x * a.y) - (a.y * b.x + b.y * c.x + c.y * a.x));

}

long long crossProduct (Point a, Point b, Point c) {
	long long v1 = (long long)(b.x - a.x) * (long long)(c.y - a.y);
	long long v2 = (long long)(b.y - a.y) * (long long)(c.x - a.x);
	return v1-v2;
}

Point* convHull(Point* points, int size) {
	int hullsize = 0;
	int hullcap = 4;
	Point* hull = calloc(hullcap, sizeof(Point));
        qsort(points, size, sizeof(*points), pointCompare);
	//one by one
	for(int i = 0; i<size; i++) {
		//printf("point %d: %llu, %llu \n", i, points[i].x, points[i].y);	
		
		if(hullsize >= 2) printf("area here: %lld\n", crossProduct(hull[hullsize-2], hull[hullsize-1], points[i]));	
		while(hullsize >= 2 && crossProduct(hull[hullsize-2], hull[hullsize-1], points[i]) <= 0) {
			memset(hull+hullsize-1, 0, sizeof(Point));
			hullsize--;	
		}
		
		//before adding, check if we need to increase our array size
		if(hullsize == hullcap) {
			hullcap<<=1;
			hull = realloc(hull, hullcap*sizeof(Point));
		}

		//add point at i
		hull[hullsize] = points[i];
		hullsize++;
		
	}
	
	for(int i = size-2, t = hullsize+1; i>=0; i--) {
		while(hullsize >= t && crossProduct(hull[hullsize-2], hull[hullsize-1], points[i]) <= 0 ) {
			memset(hull+hullsize-1, 0, sizeof(Point));
			hullsize--;
		}
		
		//before adding, check if we need to increase our array size
		if(hullsize == hullcap) {
			hullcap<<=1;
			hull = realloc(hull, hullcap*sizeof(Point));
		}

		//add point at i
		hull[hullsize] = points[i];
		hullsize++;

	}
	
	
	memset(hull+hullsize-1, 0, sizeof(Point));
	hullsize--;
	//output
	finalhullsize = hullsize;
	return hull;

}

unsigned long long rotatingCaliper(Point* hull) {
	if(finalhullsize <= 1) return 0;
	if(finalhullsize == 2) return dist(hull[0], hull[1]);
	int n = finalhullsize;
	int k = 1;
	
	//finding the farthest vertex from hull[0] & hull[n-1]
	while(  crossProduct(hull[n-1], hull[0], hull[(k+1) % n]) > crossProduct(hull[n-1], hull[0], hull[k])  ) {
		k+=1;
	}

	unsigned long long res = 0;

	for(int i = 0; i<(k+1); i++) {
		int j=(i+1)%n;
	}

}

int main(int argc, char** argv) {
	FILE* fp = NULL;
	//buffer & len for input
	fp = fopen(*(argv+1), "r");
	if (fp == NULL) {
		printf("Error opening file. Make sure file exists.\\n");
		return -1; // Exit the program with an error
	}
	

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
				
	}

	Point* convexHull = convHull(arr, dataSize);
	sum = rotatingCalipers(convexHull);


	for(int i = 0; i<finalhullsize; i++) {
		printf("Point %d: %llu, %llu \n", i, (convexHull+i)->x, (convexHull+i)->y);
	}

	printf("ending area is %llu\n", sum);
}
