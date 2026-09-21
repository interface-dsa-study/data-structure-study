#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 정수 swap
void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

// 선택정렬
void selectionSort(int *array, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (array[i] > array[j]) {
        swap(&array[i], &array[j]);
      }
    }
  }
}

// 선택정렬 역순
void selectionSortDescending(int *array, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (array[i] < array[j]) {
        swap(&array[i], &array[j]);
      }
    }
  }
}

// 삽입 정렬
void insertionSort(int *array, int size) {
  for (int i = 1; i < size; i++) {
    for (int j = i; j > 0; j--) {
      if (array[j - 1] > array[j]) {
        swap(&array[j - 1], &array[j]);
      }
    }
  }
}

void task1(int *first_array, int *second_array, int size) {
  // 선택정렬 시간 측정
  printf("=====실헙 1 시작=====\n");
  clock_t start_time_mills = clock();
  selectionSort(first_array, size);
  clock_t end_time_mills = clock();
  double duration_mills = (double) (end_time_mills - start_time_mills) / CLOCKS_PER_SEC;
  printf("실험 1 선택정렬 시간: %f\n", duration_mills);

  // 삽입정렬 시간 측정
  start_time_mills = clock();
  insertionSort(second_array, size);
  end_time_mills = clock();
  duration_mills = (double) (end_time_mills - start_time_mills) / CLOCKS_PER_SEC;
  printf("실험 1 삽입정렬 시간: %f\n", duration_mills);
  printf("=====실헙 1 종료=====\n");
}

void task2(int *first_array, int *second_array, int size) {
  printf("=====실헙 2 시작=====\n");
  // 정렬 진행
  selectionSort(first_array, size);
  selectionSort(second_array, size);

  // 선택정렬 시간측정
  clock_t start_time_mills = clock();
  selectionSort(first_array, size);
  clock_t end_time_mills = clock();
  double duration_mills = (double) (end_time_mills - start_time_mills) / CLOCKS_PER_SEC;
  printf("실험 2 선택정렬 시간: %f\n", duration_mills);

  // 삽입정렬 시간측정
  start_time_mills = clock();
  insertionSort(second_array, size);
  end_time_mills = clock();
  duration_mills = (double) (end_time_mills - start_time_mills) / CLOCKS_PER_SEC;
  printf("실험 2 삽입정렬 시간: %f\n", duration_mills);

  printf("=====실헙 2 종료=====\n");
}

void task3(int *first_array, int *second_array, int size) {
  printf("=====실헙 3 시작=====\n");

  // 역순 정렬 진행
  selectionSortDescending(first_array, size);
  selectionSortDescending(second_array, size);

  // 선택정렬 시간측정
  clock_t start_time_mills = clock();
  selectionSort(first_array, size);
  clock_t end_time_mills = clock();
  double duration_mills = (double) (end_time_mills - start_time_mills) / CLOCKS_PER_SEC;
  printf("실험 3 선택정렬 시간: %f\n", duration_mills);

  // 삽입정렬 시간측정
  start_time_mills = clock();
  insertionSort(second_array, size);
  end_time_mills = clock();
  duration_mills = (double) (end_time_mills - start_time_mills) / CLOCKS_PER_SEC;

  printf("실험 3 삽입정렬 시간: %f\n", duration_mills);
  printf("=====실헙 3 종료=====\n");
}

int main(void) {
  int n;

  scanf("%d", &n);

  // 1번 배열 동적할당
  int *first_array = malloc(sizeof(*first_array) * n);
  if (first_array == NULL) {
    exit(EXIT_FAILURE);
  }

  // 2번 배열 동적할당
  int *second_array = malloc(sizeof(*second_array) * n);
  if (second_array == NULL) {
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n; i++) {
    // 난수 생성
    int random_integer = rand();
    first_array[i] = random_integer;
    second_array[i] = random_integer;
  }

  // task1(first_array, second_array, n);
  // task2(first_array, second_array, n);
  task3(first_array, second_array, n);

  // 동적 메모리 해제
  free(first_array);
  free(second_array);

  return EXIT_SUCCESS;
}
