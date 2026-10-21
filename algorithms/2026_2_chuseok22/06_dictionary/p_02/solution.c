#include <stdio.h>
#include <stdlib.h>

int binarySearch(int *array, int left, int right, int key) {
  while (left <= right) {
    int middle = (left + right) / 2;

    if (array[middle] == key) {
      return middle;
    }
    if (array[middle] > key) {
      right = middle - 1;
    } else {
      left = middle + 1;
    }
  }
  return left;
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

  int result = binarySearch(array, 0, n - 1, k);
  printf(" %d", result);


  free(array);
  return EXIT_SUCCESS;
}
