#include <stdio.h>
#include <stdlib.h>

void printArray(int *array, int size) {
  for (int i = 0; i < size; i++) {
    printf(" %d", array[i]);
  }
}

int main(void) {
  int size;

  scanf("%d", &size);

  int *array = malloc(sizeof(*array) * size);
  if (array == NULL) {
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < size; i++) {
    scanf("%d", &array[i]);
  }

  for (int i = size - 1; i > 0; i--) {
    int max_index = 0;
    for (int j = 0; j < i; j++) {
      if (array[j] > array[max_index]) {
        max_index = j;
      }
    }
    if (array[max_index] > array[i]) {
      int tmp = array[i];
      array[i] = array[max_index];
      array[max_index] = tmp;
    }
  }

  printArray(array, size);
  free(array);
  return 0;
}
