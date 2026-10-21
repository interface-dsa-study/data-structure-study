#include <stdio.h>
#include <stdlib.h>

typedef struct PartitionResult {
  int equal_start_index;
  int equal_end_index;
} PartitionResult;

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int findPivot(int left_index, int right_index) {
  // left_index ~ right_index 랜덤 값 반환
  return rand() % (right_index - left_index + 1) + left_index;
}

PartitionResult inPlacePartition(int *array, int left_index, int right_index, int pivot_index) {
  // pivot 값 설정
  int pivot = array[pivot_index];

  // pivot 을 배열의 마지막 위치로 이동
  swap(&array[pivot_index], &array[right_index]);

  // less_index, greater_index, search_index 선언
  int less_index = left_index;
  int search_index = left_index;
  int greater_index = right_index - 1;

  while (search_index <= greater_index) {
    // pivot 보다 작으면 앞쪽으로 이동 -> less_index++, search_index++
    if (array[search_index] < pivot) {
      swap(&array[less_index], &array[search_index]);
      less_index++;
      search_index++;
    }

    // pivot 과 같으면 pass -> search_index++
    else if (array[search_index] == pivot) {
      search_index++;
    }

    // pivot 보다 크면 swap -> greater_index--
    else if (array[search_index] > pivot) {
      swap(&array[search_index], &array[greater_index]);
      greater_index--;
      // 아직 swap 한 값은 비교하지 않았으므로 search_index 는 유지
    }
  }

  // 종료 후 pivot 원상복귀
  // 종료 후 search_index 는 무조건 pivot 보다 큰 쪽에 있음
  // 이 교환을 통해 search_index 위치가 equal_end_index 와 같아짐
  swap(&array[search_index], &array[right_index]);

  // 종료 후 위치
  // less_index = equal_start_index
  // search_index = equal_end_index + 1
  PartitionResult partition_result;
  partition_result.equal_start_index = less_index;
  partition_result.equal_end_index = search_index;

  return partition_result;
}

void inPlaceQuickSort(int *array, int left_index, int right_index) {
  // 크기가 1 이면 종료
  if (left_index >= right_index) {
    return;
  }

  // pivot_index 랜덤 설정
  int pivot_index = findPivot(left_index, right_index);

  // equal_start_index, equal_end_index 추출
  PartitionResult partition_result = inPlacePartition(array, left_index, right_index, pivot_index);
  inPlaceQuickSort(array, left_index, partition_result.equal_start_index - 1);
  inPlaceQuickSort(array, partition_result.equal_end_index + 1, right_index);
}

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

  inPlaceQuickSort(array, 0, n - 1);
  printArray(array, n);

  free(array);
}
