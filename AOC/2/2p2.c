#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

//dial variable
unsigned long long sum = 0;

//SO BASICALLY I MISINTERPRETED THE INSTRUCTIONS
//this code checks if a value range has values that contain any sequence!
//ie 2121212121 is 21 repeating

int containsRep(char* str, int len) {
	//return 1 on repetition
	int ret = 0;
	//loop through j length sequences
	for(int j = 1; j<len; j++) {
		//check for repeating length correctness
		if(len%j == 0 && len != j) {
			//var for repeat
			char rep[j+1];
			memset(rep, 0, sizeof(rep));
			strncpy(rep, str, j);
			//printf("rep: %s c: %d\n", rep, j);
			//printf("str: %s\n", intString);	
			rep[j] = '\0';
			//loop through string with respect to value
			for(int k = 0; k<len; k+=j) {
				//loop through value to check
				for(int l = 0; l<j; l++) {
					//printf("%c %c\n", rep[l], intString[k+l]);
					if(rep[l] != str[k+l]) {
						ret = 1;
					}
				}
			}
			//printf("%d\n", neq);
			//if(!neq) printf("hit %d\n", i);
			//if(!neq) sum+=i;
		}
	}
	return ret;


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
	size_t len = 0;
	if(getline(&buf, &len, fp) == -1) {
		printf("input error\n");
	}
	//DELIMS
	char* DELIM1 = ",";
	char* DELIM2 = "-";
	//save values
	char *out_save, *in_save;
	//outer val
	char* range = strtok_r(buf, DELIM1, &out_save);
	//inner vals
	char *num1, *num2;
	//loop over range
	while(range != NULL) {
		//start of range
		num1 = strtok_r(range, DELIM2, &in_save);
		//end of range
		num2 = strtok_r(NULL, DELIM2, &in_save);
		//loop through range
		for(long long i = strtoll(num1, NULL, 10); i<=strtoll(num2, NULL, 10); i++){
			//bool to check if it's all equal
			bool neq = false;
			//char buffer for current Int String
			char intString[strlen(num2)+1];
			snprintf(intString, strlen(num2)+1, "%lld", i);
			//printf("readed: %s\n", intString);
			//len of current Int String
			int lenI = strlen(intString);
			for(int j = 1; j<lenI; j++) {
				//check for repeating length correctness
				if(lenI%j == 0 && lenI != j) {
					neq = false;
					//var for repeat
					char rep[j+1];
					memset(rep, 0, sizeof(rep));
					strncpy(rep, intString, j);
					//printf("rep: %s c: %d\n", rep, j);
					//printf("str: %s\n", intString);	
					rep[j] = '\0';
					//loop through string with respect to value
					for(int k = 0; k<lenI; k+=j) {
						//loop through value to check
						for(int l = 0; l<j; l++) {
							//printf("%c %c\n", rep[l], intString[k+l]);
							if(rep[l] != intString[k+l]) {
								//printf("neq at rep%d: %c str%d: %c\n", l, rep[l], k+l, intString[k+l]);	
								neq = true;
								break;
							}
						}
					}
					//printf("%d\n", neq);
					if(!neq)
					{
						//printf("hit %lld\n", i);
						sum+=i;
						break;
					}
				}

			}

			//printf("%s\n", intString);	
		}
		range = strtok_r(NULL, DELIM1, &out_save);
	}

	printf("%lld\n", sum);
}
