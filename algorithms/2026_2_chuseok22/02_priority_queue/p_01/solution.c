#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
  // 정수 swap
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void selection_sort(int *array, int size) {
  // i 는 뒤에서부터 조회
  for (int i = size - 1; i > 0; i--) {
    for (int j = 0; j < i; j++) {
      // j 는 index 0 부터 i - 1 까지 순회
      if (array[i] < array[j]) {
        swap(&array[i], &array[j]);
      }
    }
  }
}

void print_array(int *array, int size) {
  // 배열 순회하여 원소 출력
  for (int i = 0; i < size; i++) {
    printf(" %d", array[i]);
  }
  printf("\n");
}

int main(void) {
  int n;

  scanf("%d", &n);

  // 크기 N 배열 동적할당
  int *array = malloc(sizeof(*array) * n);
  if (array == NULL) {
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n; i++) {
    scanf("%d", &array[i]);
  }

  selection_sort(array, n);
  print_array(array, n);

  free(array);
  return EXIT_SUCCESS;
}
