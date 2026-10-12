#include <stdio.h>
int heap[101];
int heap_size = 0;

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void downHeap(int index) {
  int left_child_index = index * 2;
  int right_child_index = index * 2 + 1;

  // 왼쪽 자식이 없으면 종료
  if (left_child_index > heap_size) {
    return;
  }

  // 왼쪽 자식이 더 크다고 가정
  int large_child_index = left_child_index;
  // 오른쪽 자식이 존재하고, 왼쪽 자식보다 더 큰 경우
  if (right_child_index <= heap_size && heap[right_child_index] > heap[left_child_index]) {
    large_child_index = right_child_index;
  }

  // 부모가 더 큰경우 swap 하지않고 종료
  if (heap[index] >= heap[large_child_index]) {
    return;
  }
  swap(&heap[index], &heap[large_child_index]);
  downHeap(large_child_index);
}

void rBuildHeap(int index) {
  if (index > heap_size) {
    return;
  }

  int left_child_index = index * 2;
  int right_child_index = index * 2 + 1;
  rBuildHeap(left_child_index);
  rBuildHeap(right_child_index);
  downHeap(index);
}

void inPlaceHeapSort(void) {
  // 상향식 힙 생성
  rBuildHeap(1);
  
  int original_heap_size = heap_size;

  // Heap 원소가 하나 남을 때까지 반복
  while (heap_size > 1) {
    // root 와 마지막 원소 교환
    swap(&heap[1], &heap[heap_size]);

    // heap_size 감소
    heap_size--;

    // root 에 대해서 downHeap 수행
    downHeap(1);
  }

  heap_size = original_heap_size;
}

void printArray(void) {
  for (int i = 1; i <= heap_size; i++) {
    printf(" %d", heap[i]);
  }
  printf("\n");
}

int main(void) {
  scanf("%d", &heap_size);
  for (int i = 1; i <= heap_size; i++) {
    scanf("%d", &heap[i]);
  }

  inPlaceHeapSort();
  printArray();
}
