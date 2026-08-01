#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

void insert_sort(int* array, int len) {
    int i, j, temp;
    for (i = 0;i < len;i++) {
        j = i;
        while (j >-1) {
            if (array[i] < array[j]) {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
                if (i == 0) {
                    break;
                }
                i--;
            }
            j--;
        }
    }
}

int main() {
    int* array = NULL;
    int N, i;

    scanf("%d", &N);

    array = malloc(N * sizeof(int));

    for (i = 0;i < N;i++) {
        scanf("%d", &array[i]);
    }

    insert_sort(array, N);

    for (i = 0;i < N;i++) {
        printf(" %d", array[i]);
    }

    free(array);

    return 0;
}