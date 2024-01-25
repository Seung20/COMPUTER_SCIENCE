#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 10000000
#define MAX_PATTERN_SIZE 3000

char str[MAX_STRING_SIZE];
char pat[MAX_PATTERN_SIZE];


int main(void){
	FILE* fp_str = fopen("string.txt", "r");
	FILE* fp_pat = fopen("pattern.txt", "r");
	FILE* fp_res = fopen("result_naive.txt", "w");

	if(!fp_str){
		printf("The String File does not exist.\n");
		return 0;
	}
	if(!fp_pat){
		printf("The Pattern File dose not exist.\n");
		return 0;
	}

	fgets(str, MAX_STRING_SIZE, fp_str);
	fgets(pat, MAX_PATTERN_SIZE, fp_pat);
	
	int str_size = strlen(str);
	int pat_size = strlen(pat);
	
	int i, j = 0;
	int * result = (int*)malloc(sizeof(int) * MAX_STRING_SIZE);	
	int idx =0;
	
	for(i = 0; i < str_size - pat_size + 1; i++){
		if((str[i] == pat[0])&& ((str[i+pat_size-1] == pat[pat_size-1]))){
			for(j =1; j < pat_size-1; j++){
				if( str[i+j] != pat[j]) 
					break;
			}
		}
		if (j == pat_size - 1){
			result[idx] = i;
			idx += 1;
		}
	}
	result = (int*)realloc(result  ,sizeof(int) * (idx+1)); 
	fprintf(fp_res, "%d\n", idx);
	for(int i = 0; i < idx; i++)
		fprintf(fp_res, "%d ", result[i]);
	fprintf(fp_res, "\n");
	fclose(fp_str);
	fclose(fp_pat);
	fclose(fp_res);
	free(result);

	printf("Please check the result_naive.txt file\n");
	return 0;
}

