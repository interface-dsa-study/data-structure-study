#include <stdio.h>
#include <stdlib.h>
void swap(int *a, int *b) {
  // swap
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void inPlaceSelectionSort(int *array, int size) {
  for (int i = 0; i < size - 1; i++) {
    // minLoc 선언
    int minLoc = i;
    for (int j = i + 1; j < size; j++) {
      // array[j] 가 더 작은 경우
      if (array[minLoc] > array[j]) {
        // minLoc 업데이트
        minLoc = j;
      }
    }
    // 최종 swap
    swap(&array[minLoc], &array[i]);
  }
}

void printArray(int *array, int size) {
  // 배열 출력
  for (int i = 0; i < size; i++) {
    printf(" %d", array[i]);
  }
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

  inPlaceSelectionSort(array, n);

  printArray(array, n);

  free(array);
}
