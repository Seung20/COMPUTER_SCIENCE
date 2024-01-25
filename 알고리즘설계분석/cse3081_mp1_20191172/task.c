#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX_ROW 100
#define MAX_COL 100
#define MAX_RESULT_FILE_NAME 100

int row, col;
int arr[MAX_ROW][MAX_COL];
int sumOfArr[MAX_ROW][MAX_COL] = {0};
int temp[MAX_COL];


int max(int a, int b);
void printIdxSize(FILE * fp, int row, int col, int idx);
void scanningInputfile(FILE* fp, int arr[MAX_ROW][MAX_COL], int n, int m);
int maxSubsequenceSum1(int arr[MAX_ROW][MAX_COL], int row, int col);
int maxSubsequenceSum2(int arr[MAX_ROW][MAX_COL], int row, int col);
int maxSubsequenceSum3(int arr[MAX_ROW][MAX_COL], int row, int col);


int main(int argc, char *argv[]) {

    double start = (double)clock();

    int i, j;
    int idx = atoi(argv[2]);

    FILE *fp = fopen(argv[1], "r");

    char resultFileName[MAX_RESULT_FILE_NAME] = "result_";
    strcat(resultFileName, argv[1]);
    FILE *fp_res = fopen(resultFileName, "w");

    fscanf(fp, "%d %d", &row, &col);
    scanningInputfile(fp, arr, row, col);

    //fprint the inputfile, row, col, idx 
    fprintf(fp_res, "%s\n", argv[1]);
    printIdxSize(fp_res, row, col, idx);
 

    //fprint the result
    if (idx == 1)
        fprintf(fp_res, "%d\n", maxSubsequenceSum1(arr, row, col));
    else if (idx == 2)
        fprintf(fp_res, "%d\n", maxSubsequenceSum2(arr, row, col));
    else if (idx == 3)
        fprintf(fp_res, "%d\n", maxSubsequenceSum3(arr, row, col));
    
    double end = (double)clock();

    //checking time
    fprintf(fp_res, "%.0lf\n", (end-start));

    fclose(fp);
    fclose(fp_res);

    return 0;
}

int max(int a, int b) {
    return (a > b) ? a: b;
}

//문제 조건에 따라 row, col, idx를 출력하는 함수
void printIdxSize(FILE * fp, int row, int col, int idx){
    fprintf(fp, "%d\n", idx);
    fprintf(fp, "%d\n%d\n", row, col);
}

// inputfile에 있는 정보를 읽는 함수
void scanningInputfile(FILE *fp, int arr[MAX_ROW][MAX_COL], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(fp, "%d", &arr[i][j]);
        }
    }
}

//naive하게 모든 2차원 배열의 원소로 만들 수 있는 subrectangle을 기반으로 계산하는 함수.
//O(n^6)
int maxSubsequenceSum1(int arr[MAX_ROW][MAX_COL], int row, int col) {
    int MaxSum = INT_MIN; 
    int i, j, k, l, t, p;
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            for (k = i; k < row; k++)
                for (l = j; l < col; l++) {
                    int ThisSum = 0;
                    for (t = i; t <= k; t++) {
                        for (p = j; p <= l; p++) {
                            ThisSum += arr[t][p];
                        }
                    }
 
                    MaxSum = max(MaxSum, ThisSum);
                }
    return MaxSum;
}

//미리 sumOfArr를 만들어서 이 sumOfArr를 for loop으로 반복하며 maxsum을 찾는 함수.
//O(n^4)
int maxSubsequenceSum2(int arr[MAX_ROW][MAX_COL], int row, int col) {
    int MaxSum = INT_MIN;  
    int i, j, k, l;
    sumOfArr[0][0] = arr[0][0];

//미리 sumOfArr를 만드는 과정, i가 0일 때와 j가 0이 아닐 때, i가 0이 아닐 때와 j가 0일 떄, i와 j가 둘다 0이 아닐 때 모두 다르다.
// 1차원 배열에서는 상관없이 sumOfArr를 만들면 되지만 subrectangle은 경우가 다르다.
    for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                sumOfArr[i][j] = arr[i][j];

                if (i > 0) 
                    sumOfArr[i][j] += sumOfArr[i - 1][j];
                if (j > 0) 
                    sumOfArr[i][j] += sumOfArr[i][j - 1];
                if (i > 0 && j > 0) 
                    sumOfArr[i][j] -= sumOfArr[i - 1][j - 1];
        }
    }

// 이렇게 만든 sumOfArr를 미리 만들고, 시작 위치를 조정하며, sumOfArr를 기반으로 계산한다.
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            for (int k = i; k < row; k++) {
                for (int l = j; l < col; l++) {
                    int ThisSum = sumOfArr[k][l];

                    if (i > 0) 
                        ThisSum -= sumOfArr[i - 1][l];
                    if (j > 0) 
                        ThisSum -= sumOfArr[k][j - 1];
                    if (i > 0 && j > 0) 
                        ThisSum += sumOfArr[i - 1][j - 1];
                    
                    MaxSum = max(MaxSum, ThisSum);
                }
            }
        }
    }
    return MaxSum;
}


//temp라는 배열을 사용하여 arr값을 더하면서, 배열을 돌면서 바로바로 계산하는 함수.
//O(n^3)
int maxSubsequenceSum3(int arr[MAX_ROW][MAX_COL], int n, int m) {
    int MaxSum = INT_MIN;
    
    for (int i = 0; i < m; i++) {
        int temp[MAX_COL] = {0};

        for (int j = i; j < m; j++) {
            for (int k = 0; k < n; k++) {
                temp[k] += arr[k][j];
            }
            
            int ThisSum = 0;
            for (int k = 0; k < n; k++) {
                ThisSum += temp[k];

                MaxSum = max(MaxSum, ThisSum);
                
                if (ThisSum < 0) {
                    ThisSum = 0;
                }
            }
        }
    }
    
    return MaxSum;
}
