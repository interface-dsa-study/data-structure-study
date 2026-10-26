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

int findPivot(int left, int right) {
  return rand() % (right - left + 1) + left;
}

PartitionResult inPlacePartition(int *array, int left_index, int right_index) {
  int pivot_index = findPivot(left_index, right_index);
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

void quickSort(int *array, int left_index, int right_index) {
  if (left_index >= right_index) {
    return;
  }
  PartitionResult partition_result = inPlacePartition(array, left_index, right_index);
  quickSort(array, left_index, partition_result.equal_start_index - 1);
  quickSort(array, partition_result.equal_end_index + 1, right_index);
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

  quickSort(array, 0, n - 1);
  printArray(array, n);

  free(array);
}
