#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

// 삽입 정렬
void insertionSort(int *array, int size) {
  // index 1 ~ size - 1 까지 순회
  for (int i = 1; i < size; i++) {
    // index i 부터 1까지 순회
    for (int j = i; j > 0; j--) {
      // index j 와 j -1 정렬
      if (array[j - 1] > array[j]) {
        swap(&array[j - 1], &array[j]);
      }
    }
  }
}

// 배열 순회하여 원소 출력
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
    scanf("%d", &array[i]);
  }

  insertionSort(array, n);
  printArray(array, n);

  free(array);
  return EXIT_SUCCESS;
}
