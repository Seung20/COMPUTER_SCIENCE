#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 10000000
#define MAX_PATTERN_SIZE 3000

char str[MAX_STRING_SIZE];
char pat[MAX_PATTERN_SIZE];
int failure[MAX_PATTERN_SIZE];

void fail(char* pat, int pat_size);

int main(void) {
    FILE* fp_str = fopen("string.txt", "r");
    FILE* fp_pat = fopen("pattern.txt", "r");
    FILE* fp_res = fopen("result_kmp.txt", "w");

    if (!fp_str) {
        printf("The String File does not exist\n");
        return 0;
    }

    if (!fp_pat) {
        printf("The Pattern File does not exist\n");
        return 0;
    }

    fgets(str, MAX_STRING_SIZE, fp_str);
    fgets(pat, MAX_PATTERN_SIZE, fp_pat);

    
    int str_size = strlen(str);
    int pat_size = strlen(pat);

    fail(pat, pat_size);

    int i = 0, j = 0, idx = 0;
    int* result = (int*)malloc(sizeof(int) * MAX_STRING_SIZE);

    while (i < str_size) {
        if (str[i] == pat[j]) {
            i++;
            j++;

            if (j == pat_size) {
                result[idx] = i - pat_size;
                idx++;
                j = failure[j - 1] + 1;
            }
        }
        else {
            if (j == 0) {
                i++;
            }
            else {
                j = failure[j - 1] + 1;
            }
        }
    }
       
    result = (int*)realloc(result, sizeof(int) * idx);
    fprintf(fp_res, "%d\n", idx);

    for (int i = 0; i < idx; i++)
        fprintf(fp_res, "%d ", result[i]);
    fprintf(fp_res, "\n");
    free(result);
   
    printf("Please check result_kmp.txt file\n");
    fclose(fp_str);
    fclose(fp_pat);
    fclose(fp_res);

    return 0;
}

void fail(char* pat, int pat_size) {
    failure[0] = -1;
    for (int i = 1; i < pat_size; i++) {
        int j = failure[i - 1];
        while (pat[j + 1] != pat[i] && j >= 0) {
            j = failure[j];
        }

        if (pat[j + 1] == pat[i]) {
            failure[i] = j + 1;
        }
        else {
            failure[i] = -1;
        }
    }
}
