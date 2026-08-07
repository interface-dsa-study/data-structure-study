#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>

int findPivot(int start, int end) {
    int Pivot = start + rand() % (end - start + 1);

    return Pivot;
}

int inPlacePartition(int* Array, int pivot, int start, int end) {
    int temp, low = start, high = start;
    temp = Array[pivot];
    Array[pivot] = Array[end];
    Array[end] = temp;
    while (high < end) {
        if (Array[high] < Array[end]) {
            temp = Array[low];
            Array[low] = Array[high];
            Array[high] = temp;
            low++;
        }
        high++;
    }
    temp = Array[low];
    Array[low] = Array[end];
    Array[end] = temp;

    return (low);
}

void quickSort(int* Array, int pivot, int start, int end) {
    if (start >= end) {
        return;
    }
    pivot = findPivot(start, end);
    int index = inPlacePartition(Array, pivot, start, end);
    quickSort(Array, pivot, start, index - 1);
    quickSort(Array, pivot, index + 1, end);
}

int main() {
    int* sortArray = NULL;
    int N, i, middle = 0, pivot = 0;
    int start, end;

    scanf("%d", &N);

    sortArray = malloc(N * sizeof(int));

    for (i = 0;i < N;i++) {
        scanf("%d", &sortArray[i]);
    }

    start = 0;
    end = N - 1;

    quickSort(sortArray, pivot, start, end);

    for (i = 0;i < N;i++) {
        printf(" %d", sortArray[i]);
    }

    return 0;
}