#include <stdio.h>
int heap[100];
int heap_size = 0;

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void downHeap(int index) {
  int left_child_index = index * 2;
  int right_child_index = index * 2 + 1;
  if (left_child_index > heap_size) {
    return;
  }

  int large_child_index = left_child_index;
  if (right_child_index <= heap_size && heap[right_child_index] > heap[large_child_index]) {
    large_child_index = right_child_index;
  }

  if (heap[large_child_index] > heap[index]) {
    swap(&heap[large_child_index], &heap[index]);
    downHeap(large_child_index);
  }
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
  int original_heap_size = heap_size;
  while (heap_size > 1) {
    // root 와 마지막 swap
    swap(&heap[1], &heap[heap_size]);

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
  int key;

  scanf("%d", &heap_size);
  for (int i = 1; i <= heap_size; i++) {
    scanf("%d", &key);
    heap[i] = key;
  }

  // 최대힙 생성
  rBuildHeap(1);

  inPlaceHeapSort();

  printArray();
}
