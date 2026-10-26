#include <stdio.h>
#include <stdlib.h>

void swap(int *value1, int *value2) {
  int tmp = *value1;
  *value1 = *value2;
  *value2 = tmp;
}

int findPivot(int left, int right) {
  int random_range = right - left + 1;
  return rand() % random_range + left;
}

void inPlacePartition(int array[], int left, int right, int *equal_value_start_index, int *equal_value_end_index) {
  if (left >= right) {
    return;
  }

  // pivot 설정
  int pivot = findPivot(left, right);

  // pivot 과 마지막 값 교환
  swap(&array[pivot], &array[right]);
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

  free(array);
}
