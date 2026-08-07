#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

void merge(int* Array, int* buffer, int index) {
    int* temp = Array;
    int leftsize = index / 2;
    int rightsize = index - leftsize;
    int Arrayindex, left = 0, right = 0, i = 0;

    while (left < leftsize && right < rightsize) {
        if (Array[left] <= Array[leftsize + right]) {
            buffer[i++] = Array[left++];
        }
        else {
            buffer[i++] = Array[right+ leftsize];
            right++;
        }
    }
    while (left < leftsize) {
        buffer[i++] = Array[left++];
    }
    while(right < rightsize) {
        buffer[i++] = Array[leftsize + right];
        right++;
    }
    for (int i = 0;i < index;i++) {
        Array[i] = buffer[i];
    }

}

void mergesort(int* Array, int* buffer, int index) {
    if (index <= 1) {
        return;
    }
    mergesort(Array, buffer, index / 2);
    mergesort(Array + (index / 2), buffer, index - (index / 2));
    merge(Array, buffer, index);
}

int main() {
    int* sortArray = NULL;
    int* bufferArray = NULL;
    int N, i;

    scanf("%d", &N);

    sortArray = malloc(N * sizeof(int));

    bufferArray = malloc(N * sizeof(int));

    for (i = 0;i < N;i++) {
        scanf("%d", &sortArray[i]);
    }

    mergesort(sortArray, bufferArray, N);

    for (i = 0;i < N;i++) {
        printf(" %d", sortArray[i]);
    }

    return 0;
}