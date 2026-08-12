#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>

void BinarySearch(int* Array, int left, int right, int key) {
    if (left > right) {
        printf(" %d", left-1);
        return;
    }
    int mid = (left + right) / 2;
    if (Array[mid] == key) {
        printf(" %d", mid);
        return;
    }
    else if (Array[mid] > key) {
        BinarySearch(Array, left, mid-1, key);
    }
    else {
        BinarySearch(Array, mid+1, right, key);
    }
}

int main() {
    int* Arraylist = NULL;
    int N, key;

    scanf("%d %d", &N, &key);

    Arraylist = malloc(N * sizeof(int));

    for (int i = 0;i < N;i++) {
        scanf("%d", &Arraylist[i]);
    }

    BinarySearch(Arraylist, 0, N, key);

    return 0;
}