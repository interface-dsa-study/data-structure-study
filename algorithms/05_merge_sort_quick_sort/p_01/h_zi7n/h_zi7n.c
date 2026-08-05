#include <stdio.h>
#include <stdlib.h>

void merge(int array[], int buffer[], int left, int middle, int right) {
    int start = left;
    int start_two = middle + 1;
    int buffer_start_index = left;
    while (start == middle && start_two == right) {
        if (array[start] < array[start_two]) {
            buffer[buffer_start_index++] = array[start++];
        }
        else buffer[buffer_start_index++] = array[start_two++];
    }
    if (start == middle) {
        while (start_two != right) {
            buffer[buffer_start_index++] = array[start_two++];
        }
    }
    else {
        while (start != middle) {
            buffer[buffer_start_index++] = array[start++];
        }
    }
}

void mergeSort(int array[], int buffer[], int left, int right) {
    if (right < left) { // 종료조건
        return;
    }
    int middle = (left+right) / 2;
    mergeSort(array, buffer, left, middle);
    mergeSort(array, buffer, middle + 1, right);
    merge(array, buffer, left, middle, right);
}

int main () {
    int N; scanf("%d", &N);
    int *array = malloc(sizeof(*array)*N);
    int *buffer = malloc(sizeof (*buffer)*N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &array[i]);
    }
    mergeSort(array, buffer, 0, N - 1);
    for (int i = 0; i < N; i++) {
        array[i] = buffer[i];
        printf(" %d", array[i]);
    }
    free(array); free(buffer);
}