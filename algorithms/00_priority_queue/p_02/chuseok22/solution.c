#include <stdio.h>
#include <stdlib.h>

int *insertionSort(int *array, int size) {
  for (int i = 1; i < size; i++) {
    for (int j = i; j > 0; j--) {
      if (array[j - 1] > array[j]) {
        int tmp = array[j - 1];
        array[j - 1] = array[j];
        array[j] = tmp;
      }
    }
  }

  return array;
}

void printArray(int *array, int size) {
  for (int i = 0; i < size; i++) {
    printf(" %d", array[i]);
  }
}

int main(void) {
  int size = 0;
  scanf("%d", &size);

  int *array = malloc(sizeof(*array) * size);
  if (array == NULL) {
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < size; i++) {
    scanf("%d", &array[i]);
  }

  insertionSort(array, size);

  printArray(array, size);
  free(array);
  return 0;
}
