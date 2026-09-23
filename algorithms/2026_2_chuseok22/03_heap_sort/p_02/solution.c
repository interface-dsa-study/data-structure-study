#include <stdio.h>

/**
 * 본인 index = i
 * 부모 index = i / 2
 * 왼쪽 자식 index = i * 2
 * 오른쪽 자식 index = i * 2 + 1
 */

int heap[101];
int heap_size = 0;

void swap(int *value1, int *value2) {
  int tmp = *value1;
  *value1 = *value2;
  *value2 = tmp;
}

void downHeap(int index) {
  int left_child_index = index * 2;
  int right_child_index = index * 2 + 1;

  // 왼쪽 자식 index 가 heap_size를 초과하는 경우 종료
  if (left_child_index > heap_size || index > heap_size) {
    return;
  }

  // 왼쪽 자식 > 오른쪽 자식
  if (heap[left_child_index] > heap[right_child_index]) {
    if (heap[left_child_index] > heap[index]) {
      // 왼쪽 자식 > 부모
      swap(&heap[index], &heap[left_child_index]);
    }
    downHeap(left_child_index);
  } else {
    // 오른쪽 자식 > 왼쪽 자식
    if (heap[right_child_index] > heap[index]) {
      // 오른쪽 자식 > 부모
      swap(&heap[index], &heap[right_child_index]);
    }
    downHeap(right_child_index);
  }
}

void rBuildHeap(int index) {
  if (index > heap_size) {
    return;
  }
  int left_child_index = index * 2;
  int right_child_index = index * 2 + 1;

  // 왼쪽 서브 힙 정렬
  rBuildHeap(left_child_index);
  // 오른쪽 서브 힙 정렬
  rBuildHeap(right_child_index);
  // root 에 대해서 정렬
  downHeap(index);
}

void printHeap(void) {
  for (int i = 1; i <= heap_size; i++) {
    printf(" %d", heap[i]);
  }
  printf("\n");
}

int main(void) {
  scanf("%d", &heap_size);

  // heap 에 key 추가
  for (int i = 1; i <= heap_size; i++) {
    scanf("%d", &heap[i]);
  }

  rBuildHeap(1);
  printHeap();
}
