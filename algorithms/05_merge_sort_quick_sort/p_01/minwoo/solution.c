#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

void merge() {

}

int mergesort(int* Array, int* buffer, int index, int left, int right, int middle) {
    if (index <= 0) {
        return index;
    }
    left = mergesort(Array, buffer, index / 2, left, right, middle);
    right = mergesort(Array, buffer, index / 2, left, right, middle);
    merge();
}

int main() {
    int* sortArray = NULL;
    int N, i;

    scanf("%d", &N);

    sortArray = malloc(N * sizeof(int));

    for (i = 0;i < N;i++) {
        scanf("%d", &sortArray[i]);
    }

    return 0;
}