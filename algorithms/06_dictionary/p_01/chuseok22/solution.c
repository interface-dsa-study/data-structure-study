#include <stdio.h>
#include <stdlib.h>

int binarySearch(int *array, int target, int start_index, int end_index) {
  int middle_index = (start_index + end_index) / 2;
  if (array[middle_index] == target) {
    return middle_index;
  }

  if (start_index > end_index) {
    return end_index;
  }

  if (array[middle_index] > target) {
    // 왼쪽 탐색
    // start_index ~ middle_index - 1
    return binarySearch(array, target, start_index, middle_index - 1);
  }
  if (array[middle_index] < target) {
    // 오른쪽 탐색
    // middle_index + 1 ~ start_index
    return binarySearch(array, target, middle_index + 1, end_index);
  }
}

int main(void) {
  int n, k;

  scanf("%d %d", &n, &k);
  int *array = malloc(sizeof(*array) * n);
  if (array == NULL) {
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n; i++) {
    scanf("%d", &array[i]);
  }

  int result = binarySearch(array, k, 0, n - 1);

  printf(" %d", result);

  free(array);
  return EXIT_SUCCESS;
}
