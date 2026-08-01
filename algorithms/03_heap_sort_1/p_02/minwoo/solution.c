#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

int ArrayH[100];
int n;  //size

void swap(int* x, int* y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void downHeap(int index) { //buildHeap을 재귀로 
    if (ArrayH[index * 2] > ArrayH[(index * 2) + 1]) {
        if (ArrayH[index * 2] > ArrayH[index]) {
            swap(&ArrayH[index], &ArrayH[index * 2]);
        }
    }
    else {
        if (ArrayH[(index * 2) + 1] > ArrayH[index]) {
            swap(&ArrayH[index], &ArrayH[(index * 2) + 1]);
        }
    }
}

void buildHeap(int index) {
    int temp;
    if (index > 1) {
        for (int i = 1;i <= index;) {
            if (ArrayH[i * 2] > ArrayH[(i * 2) + 1]) {
                if (ArrayH[i] < ArrayH[i * 2]) {
                    swap(&ArrayH[i], &ArrayH[i * 2]);
                    i = i * 2;
                }
            }
            else if (ArrayH[i * 2] < ArrayH[(i * 2) + 1]) {
                if (ArrayH[i] < ArrayH[(i * 2) + 1]) {
                    swap(&ArrayH[i], &ArrayH[(i * 2) + 1]);
                    i = (i * 2) + 1;
                }
            }
            i *= 2;
        }
    }
}

void rBuildHeap(int index) {
    if (index > n) {
        return;
    }
    rBuildHeap(index * 2);
    rBuildHeap((index * 2) + 1);
    downHeap(index);
}

int main() {
    int N, key;

    scanf("%d", &N);

    n = N;

    for (int i = 1;i <= N;i++) {
        scanf("%d", &key);
        ArrayH[i] = key;
    }

    rBuildHeap(1);

    for (int i = 1;i <= N;i++) {
        printf(" %d", ArrayH[i]);
    }

    return 0;
}