#include <stdio.h>
#include <stdlib.h>
typedef struct Result {
  // max min 쌍 구조체
  int max;
  int min;
} Result;

// 두 정수 중 최댓값 반환
int max(int a, int b) {
  if (a >= b) {
    return a;
  }
  return b;
}

// 두 정수 중 최솟값 반환
int min(int a, int b) {
  if (a >= b) {
    return b;
  }
  return a;
}

Result rArrayMaxMin(int *array, int left, int right) {
  Result result;
  if (left >= right) {
    // array 크기가 1인경우 max, min 모두 같은 값 반환
    result.max = array[left];
    result.min = array[left];
    return result;
  }

  // 중간 인덱스
  int mid = (left + right) / 2;
  Result result_left, result_right;
  // 재귀
  result_left = rArrayMaxMin(array, left, mid);
  result_right = rArrayMaxMin(array, mid + 1, right);

  // 양쪽에서 최대, 최소 비교
  int largest = max(result_left.max, result_right.max);
  int smallest = min(result_left.min, result_right.min);

  // 최종 result 반환
  result.max = largest;
  result.min = smallest;
  return result;
}

Result arrayMaxMin(int *array, int n) {
  return rArrayMaxMin(array, 0, n - 1);
}

int main(void) {
  // 테스트를 위해 크기 5개짜리 배열 고정
  int array[5] = {1, 2, 3, 4, 5};

  Result result = arrayMaxMin(array, 5);
  printf("최대: %d, 최소 %d", result.max, result.min);

  return EXIT_SUCCESS;
}
