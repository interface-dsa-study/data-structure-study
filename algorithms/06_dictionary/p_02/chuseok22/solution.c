#include <stdio.h>
#include <stdlib.h>

int binarySearch(int *array, int target, int size) {
  int start_index = 0;
  int end_index = size - 1;

  while (start_index <= end_index) {
    int middle_index = start_index + (end_index - start_index) / 2;

    if (array[middle_index] < target) {
      // 뒤쪽 탐색
      start_index = middle_index + 1;
    } else {
      // 앞쪽 탐색
      end_index = middle_index - 1;
    }
  }

  return start_index;
}

int main(void) {
  int size, target;
  scanf("%d %d", &size, &target);

  int *array = malloc(sizeof(*array) * size);
  if (array == NULL) {
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < size; i++) {
    scanf("%d", &array[i]);
  }

  int result = binarySearch(array, target, size);

  printf(" %d\n", result);

  free(array);
  return EXIT_SUCCESS;
}
