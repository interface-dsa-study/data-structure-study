#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void insertionSort(int *array, int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = i; j >= 0; j--) {
      if (array[j] > array[j + 1]) {
        swap(&array[j], &array[j + 1]);
      } else {
        break;
      }
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

  insertionSort(array, n);

  printArray(array, n);

  free(array);
}
