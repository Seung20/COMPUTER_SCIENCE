#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define swap(a, b) {int tmp = a; a = b; b= tmp;}

void InsertionSort(int *, int);

int Partition(int* ,int , int);
void QuickSort(int * , int , int );

void MergeSort(int *, int, int );
void merge(int *, int, int , int);

void FastestSort(int *, int, int );
void DualPivotQuickSort(int *arr, int left, int right);
int dualPivotPartition(int *arr, int left, int right, int *lp, int *rp);


int n; 
//number of elements
int* arr;
int* merged_sorted_arr;
//정렬할 array

int main(int argc, char * argv[])
{
    clock_t startTime, endTime;
    double runtime;

    FILE * fp = fopen(argv[1], "r");
    
    char resultName[300] = "result_";
    strcat(resultName, argv[2]);
    strcat(resultName, "_");
    strcat(resultName, argv[1]);
    int AlgorithmNum = atoi(argv[2]);
    FILE *fp_res = fopen(resultName, "w");
       
    fscanf(fp, "%d", &n);
    
    arr = (int*)malloc(sizeof(int) * n); 
    merged_sorted_arr=(int*)malloc(sizeof(int) * n); 
    for(int i = 0; i < n; i++)
    {
         fscanf(fp, "%d", &arr[i]);
    }
    
    
    startTime = clock();
    switch(AlgorithmNum){
        case 1:
            InsertionSort(arr , n);
            break;
        case 2:
            QuickSort(arr, 0, n-1);
            break;
        case 3:
            MergeSort(arr , 0 , n-1);
            break;
        case 4:
            FastestSort(arr , 0, n-1);
            break;
    }
    endTime = clock();
    runtime = endTime - startTime;
    
    //fprintf 
    fprintf(fp_res, "%s\n", argv[1]);
    fprintf(fp_res,"%d\n", AlgorithmNum);
    fprintf(fp_res, "%d\n", n);
    fprintf(fp_res, "%lf\n", runtime/CLOCKS_PER_SEC);
    
    for(int i = 0 ; i < n; i++){
        fprintf(fp_res,"%d ", arr[i]);
    }
    fprintf(fp_res, "\n");

    fclose(fp);
    free(arr);
    free(merged_sorted_arr);
    fclose(fp_res);
    return 0;
}

void InsertionSort(int * list, int n){
    int i, j, key;
    for(i = 1; i < n; i++){
        key = arr[i];

        for(j = i - 1; j >= 0 && arr[j] > key; j--){
            arr[j+1] = arr[j];
        }

        arr[j+1] = key;
    }
}

void QuickSort(int* arr, int left, int right){
    if(left < right){
        int pivot = Partition(arr, left, right);
        QuickSort(arr,left,pivot-1);
        QuickSort(arr,pivot+1,right);
    }
 }

int Partition(int* arr, int left, int right) {

    int i = left - 1;
    int pivot = arr[right];
 
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[right]);

    return i + 1;
}

void merge(int *list, int start, int mid, int end) {
    int i = start;
    int j = mid + 1;
    int k = start;
    int x;

    while (i <= mid && j <= end) {
        if (list[i] <= list[j]) {
            merged_sorted_arr[k++] = list[i++];
        } else {
            merged_sorted_arr[k++] = list[j++];
        }
    }

    while (i <= mid) {
        merged_sorted_arr[k++] = list[i++];
    }

    while (j <= end) {
        merged_sorted_arr[k++] = list[j++];
    }

    for (x = start; x <= end; x++) {
        list[x] = merged_sorted_arr[x];
    }
}


void MergeSort(int * list, int start, int end){
    int mid;
    if(start < end){
        mid = (start + end) / 2;
        MergeSort(list, start, mid);
        MergeSort(list, mid + 1, end);
        merge(list, start, mid, end);
    }
}

void FastestSort(int *arr, int left, int right) {
    if (right - left <= 16) {
        InsertionSort(arr + left, right - left + 1);
    } else {
        int lp, rp;
        DualPivotQuickSort(arr, left, right);
    }
}

void DualPivotQuickSort(int *arr, int left, int right) {
    if (left < right) {
        int lp, rp;
        int k = dualPivotPartition(arr, left, right, &lp, &rp);
        DualPivotQuickSort(arr, left, lp - 1);
        DualPivotQuickSort(arr, lp + 1, rp - 1);
        DualPivotQuickSort(arr, rp + 1, right);
    }
}

int dualPivotPartition(int *arr, int left, int right, int *lp, int *rp) {
    if (arr[left] > arr[right]) {
        swap(arr[left], arr[right]);
    }

    int j = left + 1;
    int g = right - 1, k = left + 1, p = arr[left], q = arr[right];

    while (k <= g) {
        if (arr[k] < p) {
            swap(arr[k], arr[j]);
            j++;
        } else if (arr[k] >= q) {
            while (arr[g] > q && k < g) {
                g--;
            }

            if (arr[g] >= p) {
                swap(arr[k], arr[g]);
            } else {
                swap(arr[k], arr[j]);
                swap(arr[j], arr[g]);
                j++;
            }

            g--;
        }
        k++;
    }

    j--;
    g++;

    swap(arr[left], arr[j]);
    swap(arr[right], arr[g]);

    *lp = j;
    *rp = g;

    return k - 1;
}