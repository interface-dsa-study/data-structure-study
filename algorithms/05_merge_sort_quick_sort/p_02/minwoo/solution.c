#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>

int findPivot(int start, int end) {
    int Pivot = start + rand() % (end - start + 1);

    return Pivot;
}

void quickSort(int* Array, int pivot, int start, int end) {

    pivot = findPivot(start, end);

    // 피벗 맨 오른쪽으로 이동시킨 후 피벗 기준으로 정렬
    // 정렬된 부분들 안에서 또 피벗을 정하고 그 피벗을 기준으로 정렬
}

int main() {
    int* sortArray = NULL;
    int N, i, middle = 0;

    scanf("%d", &N);

    sortArray = malloc(N * sizeof(int));

    for (i = 0;i < N;i++) {
        scanf("%d", &sortArray[i]);
    }

    return 0;
}