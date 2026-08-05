#include <stdio.h>
#include <stdlib.h>

void merge(int array[], int buffer[], int left, int middle, int right) {
  int left_index = left;
  int right_index = middle + 1;
  int buffer_index = left;

  while (left_index <= middle && right_index <= right) {
    if (array[left_index] <= array[right_index]) {
      buffer[buffer_index] = array[left_index];
      left_index++;
    } else {
      buffer[buffer_index] = array[right_index];
      right_index++;
    }
    buffer_index++;
  }

  // 왼쪽 배열 남은 원소
  while (left_index <= middle) {
    buffer[buffer_index] = array[left_index];
    left_index++;
    buffer_index++;
  }

  // 오른쪽 배열 남은 원소
  while (right_index <= right) {
    buffer[buffer_index] = array[right_index];
    right_index++;
    buffer_index++;
  }

  for (int i = left; i <= right; i++) {
    array[i] = buffer[i];
  }
}

void mergeSort(int array[], int buffer[], int left, int right) {
  if (left >= right) {
    return;
  }

  int middle = (left + right) / 2;
  mergeSort(array, buffer, left, middle);
  mergeSort(array, buffer, middle + 1, right);
  merge(array, buffer, left, middle, right);
}

int main(void) {
  int size;
  scanf("%d", &size);

  int *array = malloc(sizeof(*array) * size);
  if (array == NULL) {
    exit(EXIT_FAILURE);
  }

  int *buffer = malloc(sizeof(*buffer) * size);
  if (buffer == NULL) {
    free(array);
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < size; i++) {
    scanf("%d", &array[i]);
  }

  mergeSort(array, buffer, 0, size - 1);

  for (int i = 0; i < size; i++) {
    printf(" %d", array[i]);
  }

  free(array);
  free(buffer);
}
