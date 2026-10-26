#include <stdio.h>
#include <stdlib.h>

int heap[100];
int current_heap_size = 0;

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void downHeap(int index) {
  int left_child_index = index * 2;
  int right_child_index = index * 2 + 1;

  if (left_child_index > current_heap_size) {
    return;
  }

  int large_child_index = left_child_index;
  if (right_child_index <= current_heap_size && heap[right_child_index] > heap[left_child_index]) {
    large_child_index = right_child_index;
  }

  // 부모와 비교
  if (heap[large_child_index] > heap[index]) {
    swap(&heap[large_child_index], &heap[index]);
    downHeap(large_child_index);
  }
}

void rBuildHeap(int index) {
  int left_child_index = index * 2;
  int right_child_index = index * 2 + 1;

  if (index > current_heap_size) {
    return;
  }

  rBuildHeap(left_child_index);
  rBuildHeap(right_child_index);
  downHeap(index);
}

void buildHeap(void) {
  for (int i = current_heap_size / 2; i >= 1; i--) {
    downHeap(i);
  }
}

void printHeap(void) {
  for (int i = 1; i <= current_heap_size; i++) {
    printf(" %d", heap[i]);
  }
  printf("\n");
}

int main(void) {
  int key;
  scanf("%d", &current_heap_size);

  for (int i = 1; i <= current_heap_size; i++) {
    scanf("%d", &key);
    heap[i] = key;
  }

  // rBuildHeap 호출
  // rBuildHeap(1);

  // buildHeap 호출
  buildHeap();

  printHeap();

  return EXIT_SUCCESS;
}
