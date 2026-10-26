#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int heap[100];
int current_heap_size = 0;

/**
 * 본인 i
 * 부모 i / 2
 * 왼쪽 자식 i * 2
 * 오른쪽 자식 i * 2 + 1
 */

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void upHeap(int index) {
  int parent_index = index / 2;
  if (parent_index < 1) {
    return;
  }

  // 부모와 비교
  if (heap[index] > heap[parent_index]) {
    swap(&heap[index], &heap[parent_index]);
    upHeap(parent_index);
  }
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

  if (heap[index] >= heap[large_child_index]) {
    return;
  }

  swap(&heap[large_child_index], &heap[index]);
  downHeap(large_child_index);
}

void insertItem(int key) {
  current_heap_size++;
  heap[current_heap_size] = key;
  upHeap(current_heap_size);
  printf("0\n");
}

int removeMax(void) {
  // 루트 원소 (삭제)
  int removed_key = heap[1];

  // 루트에 마지막 원소 복사
  heap[1] = heap[current_heap_size];
  // 마지막 원소 0 초기화
  heap[current_heap_size] = 0;
  // Heap 사이즈 감소
  current_heap_size--;

  downHeap(1);
  return removed_key;
}

void printHeap(void) {
  for (int i = 1; i <= current_heap_size; i++) {
    printf(" %d", heap[i]);
  }
  printf("\n");
}

int main(void) {
  int value;
  char command;

  while (true) {
    scanf(" %c", &command);
    if (command == 'i') {
      scanf(" %d", &value);
      insertItem(value);
    } else if (command == 'd') {
      int removed_key = removeMax();
      printf("%d\n", removed_key);
    } else if (command == 'p') {
      printHeap();
    } else if (command == 'q') {
      return EXIT_SUCCESS;
    } else {
      return EXIT_FAILURE;
    }
  }
}
