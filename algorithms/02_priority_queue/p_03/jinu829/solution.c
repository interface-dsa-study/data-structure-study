#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

void selectionSort(int *arr, int n)
{
    int max;
    int maxindex;
    int tmp;
    for (int i = n-1; i > 0; i--){
        max = 0;
        maxindex = 0;
        for (int j = 0; j <= i; j++){
            if (arr[j] > max){
                max = arr[j];
                maxindex = j;
            }
        }
        tmp = arr[i];
        arr[i] = arr[maxindex];
        arr[maxindex] = tmp;
    }
}

void insertSort(int *arr, int n)
{
    int tmp;
    for (int i = 1; i < n; i++){
        for (int j = 0; j < i; j++){
            if (arr[i] < arr[j]){
                tmp = arr[i];
                for (int k = i - 1; k >= j; k--){
                    arr[k + 1] = arr[k];
                }
                arr[j] = tmp;
                break;
            }
        }
    }
}


int main(){
    int n;
    int *A = NULL;
    int *B = NULL;
    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;

    scanf("%d", &n);
    A = (int *)malloc(sizeof(int) * n);
    B = (int *)malloc(sizeof(int) * n);
    if (A == NULL || B == NULL)
    {
        printf("잘못된 공간에 접속하였습니다.");
        return 0;
    }

    srand(time(NULL));
    for (int i = 0; i < n; i++){
        A[i] = rand() % 1000;
        B[i] = A[i];
    }

    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    selectionSort(A, n);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("time: %.12f ms\n\n", ((double)diff.QuadPart/(double)ticksPerSec.QuadPart) * 1000);


    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    insertSort(B, n);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("time: %.12f ms\n\n", ((double)diff.QuadPart/(double)ticksPerSec.QuadPart) * 1000);

    free(A);
    free(B);
    return 0;
}