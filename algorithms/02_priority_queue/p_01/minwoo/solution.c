#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

void selection_sort(int *arr, int len) {
    int i, j, temp, changenum;

    for (i = 0; ;i++) {
        changenum = 0;
        for (j = 0;j < len;j++) {
            if (arr[changenum] <= arr[j]) {
                changenum = j;
            }
        }
        len--;
        if (len == -1) {
            break;
        }
        temp = arr[changenum];
        arr[changenum] = arr[len];
        arr[len] = temp;
    }
}

int main() {
    int* Arr;
    int N, i;

    scanf("%d", &N);

    Arr = malloc(sizeof(int) * N);

    for (i = 0;i < N;i++) {
        scanf("%d", &Arr[i]);
    }

    selection_sort(Arr, N);

    for (i = 0;i < N;i++) {
        printf(" %d", Arr[i]);
    }


    return 0;
}