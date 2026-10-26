#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void selectionSort(int *array, int size) {
  for (int i = size - 1; i > 0; i--) {
    int max_index = 0;
    for (int j = 0; j < i; j++) {
      if (array[j] > array[max_index]) {
        max_index = j;
      }
    }
    if (array[max_index] > array[i]) {
      swap(&array[max_index], &array[i]);
    }
  }
}

void printArray(int *array, int size) {
  for (int i = 0; i < size; i++) {
    printf(" %d", array[i]);
  }
  printf("\n");
}

int main(void) {
  int n;
  scanf("%d", &n);

  int *array = malloc(sizeof(*array) * n);
  if (array == NULL) {
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n; i++) {
    scanf(" %d", &array[i]);
  }

  selectionSort(array, n);
  printArray(array, n);
  return EXIT_SUCCESS;
}
