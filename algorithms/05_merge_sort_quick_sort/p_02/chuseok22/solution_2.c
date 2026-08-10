#include <stdio.h>
#include <stdlib.h>

void swap(int *value1, int *value2) {
  int tmp = *value1;
  *value1 = *value2;
  *value2 = tmp;
}

void quickSort(int array[], int left, int right) {
  if (left >= right) {
    return;
  }

  int pivot = array[right];
  int a = left - 1;
  int b = left;

  for (; b < right; b++) {
    if (array[b] < pivot) {
      a++;
      swap(&array[a], &array[b]);
    }
  }

  a++;
  swap(&array[a], &array[right]);

  quickSort(array, left, a - 1);
  quickSort(array, a + 1, right);
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

  quickSort(array, 0, size - 1);

  for (int i = 0; i < size; i++) {
    printf(" %d", array[i]);
  }
  free(array);
}
