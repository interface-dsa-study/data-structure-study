#include <stdio.h>
#include <stdlib.h>

int binarySearch(int *array, int target_value, int left_index, int right_index) {
  // 더이상 탐색할 곳이 없으면 right_index 반환
  if (left_index > right_index) {
    return right_index;
  }
  int middle_index = (left_index + right_index) / 2;

  // 같으면 index 반환
  if (target_value == array[middle_index]) {
    return middle_index;
  }
  // target_value 가 더 작으면 왼쪽 search
  if (target_value < array[middle_index]) {
    return binarySearch(array, target_value, left_index, middle_index - 1);
  }
  return binarySearch(array, target_value, middle_index + 1, right_index);
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

  if (array[0] > k) {
    printf("-1\n");
    return EXIT_SUCCESS;
  }

  int index = binarySearch(array, k, 0, n - 1);
  printf(" %d\n", index);

  free(array);

  return EXIT_SUCCESS;
}
