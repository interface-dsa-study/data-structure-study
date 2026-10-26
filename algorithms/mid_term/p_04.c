#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct IndexTwin {
  int left_index;
  int right_index;
} IndexTwin;

// 전역 배열 스택 선언
IndexTwin stack[INT16_MAX];
int current_stack_size = 0;

typedef struct PartitionResult {
  int equal_start_index;
  int equal_end_index;
} PartitionResult;

bool isStackEmpty(void) {
  return current_stack_size == 0;
}

void stackPush(IndexTwin index_twin) {
  stack[current_stack_size] = index_twin;
  current_stack_size++;
}

IndexTwin stackPop(void) {
  if (isStackEmpty()) {
    fprintf(stderr, "[에러]비어있는 stack 에서 pop 발생");
  }
  IndexTwin result = stack[current_stack_size];
  current_stack_size--;
  return result;
}

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int findPivot(int left, int right) {
  return rand() % (right - left + 1) + left;
}

PartitionResult inPlacePartition(int *array, int left_index, int right_index, int pivot_index) {
  // pivot 저장
  int pivot = array[pivot_index];

  // pivot <-> 마지막 원소
  swap(&array[pivot_index], &array[right_index]);

  int start_index = left_index;
  int end_index = right_index - 1;
  int target_index = left_index;

  while (target_index <= end_index) {
    // pivot 보다 작은 경우
    if (array[target_index] < pivot) {
      swap(&array[start_index], &array[target_index]);
      start_index++;
      target_index++;
    }
    // pivot 보다 큰 경우
    else if (array[target_index] > pivot) {
      swap(&array[target_index], &array[end_index]);
      end_index--;
    }
    // pivot 과 같은 경우
    else if (array[target_index] == pivot) {
      target_index++;
    }
  }

  // pivot 원상 복귀
  swap(&array[target_index], &array[right_index]);

  PartitionResult partition_result;
  partition_result.equal_start_index = start_index;
  partition_result.equal_end_index = target_index;

  return partition_result;
}

void nonRecursiveInPlaceQuickSort(int *array, int left_index, int right_index) {
  // stack 에 (l, r) push
  IndexTwin index_twin;
  index_twin.left_index = left_index;
  index_twin.right_index = right_index;
  stackPush(index_twin);

  // stack이 비어있지 않는 동안 반복
  while (isStackEmpty()) {
    // stack 에서 pop
    IndexTwin popped_index_twin = stackPop();
    while (popped_index_twin.left_index < popped_index_twin.right_index) {
      // pivot 설정
      int pivot_index = findPivot(popped_index_twin.left_index, popped_index_twin.right_index);

      // inPlacePartition 실행
      // 반환값은 equal_start_index, equal_end_index
      PartitionResult partition_result = inPlacePartition(array, popped_index_twin.left_index, popped_index_twin.right_index, pivot_index);

      // stack 에 결과 push
      IndexTwin partition_index_twin;
      partition_index_twin.left_index = partition_result.equal_end_index + 1;
      partition_index_twin.right_index = right_index;
      stackPush(partition_index_twin);

      partition_index_twin.right_index = partition_result.equal_start_index - 1;
    }
  }
}

void printArray(int *array, int size) {
  for (int i = 0; i < size; i++) {
    printf(" %d", array[i]);
  }
}

int main(void) {
  // 테스트를 위해 크기 5개짜리 배열 고정
  int array[5] = {6, 1, 7, 9, 3};

  nonRecursiveInPlaceQuickSort(array, 0, 4);
  printArray(array, 5);
}
