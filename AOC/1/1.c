#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//dial variable
unsigned int dial = 50;

int main(int argc, char** argv) {
	unsigned int pass = 0;
	FILE* fp = NULL;
	//buffer & len for input
	fp = fopen(*(argv+1), "r");
	if (fp == NULL) {
		printf("Error opening file. Make sure file exists.\\n");
		return -1; // Exit the program with an error
	}
	char* buf;
	size_t len;
	while(getline(&buf, &len, fp) != -1) {
		printf("d%d p%d\n", dial, pass);
		printf("%s", buf);
		//character for direction
		char dir = buf[0];
		if (dir >= 'a' && dir <= 'z') {
			dir = (char)(dir - 'a' + 'A');
		}
		//rotation amount
		//number section of string
		char* amount = &*(buf+1);
		int num = atoi(amount);
		//switch statement for direction
		switch(dir) {
			case 'L':
				//check amount
				while(num > 99) {
					pass++;
					num-=100;
				}
				if(dial<num) {
					if(dial != 0) pass++;
					dial = 100-(num-dial);
				} else {
					dial = dial - num;
				}
				break;
			case 'R':
				//right rotation for add

				//loop if amount is large
				while(num > 99) {
					pass++;
					num-=100;
				}

				//check if dial hits 0 rotating right
				printf("dial%d  num%d\n", dial, num);
				if(dial+num > 99) {
					//printf("how\n");
					//calc next value
					int val = ((dial+num) % 100);
					if(val > 0) pass++;
					dial = val;
				} else {
					dial = dial + num;
				}

				break;
			default:
				return -1;

		}
		//check dial after rotation
		if(dial == 0) pass++;
	}
	if(buf) {
		free(buf);
		buf = 0;
	}
	fclose(fp);
	printf("%d\n", pass);
	return pass;
}
