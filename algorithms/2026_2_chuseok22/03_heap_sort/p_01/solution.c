#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int heap[101];
int heap_size = 0;

/**
 * 본인 i
 * 부모 i / 2
 * 왼쪽 자식 i * 2
 * 오른쪽 자식 i * 2 + 1
 */

void swapHeap(int index1, int index2) {
  int tmp = heap[index1];
  heap[index1] = heap[index2];
  heap[index2] = tmp;
}

void upHeap(int index) {
  // 루트인 경우 종료
  if (index == 1) {
    return;
  }

  int parent_index = index / 2;

  // 부모와 비교
  if (heap[parent_index] < heap[index]) {
    swapHeap(index, parent_index);
  }

  // 재귀 호출
  upHeap(parent_index);
}

void downHeap(int index) {
  int left_child_index = index * 2;
  int right_child_index = index * 2 + 1;

  if (left_child_index > heap_size) {
    return;
  }

  // 왼쪽 자식이 더 큰 경우
  if (heap[left_child_index] > heap[right_child_index]) {
    if (heap[left_child_index] > heap[index]) {
      swapHeap(left_child_index, index);
    }
    downHeap(left_child_index);
  } else {
    // 오른쪽 자식이 더 큰 경우
    if (heap[right_child_index] > heap[index]) {
      swapHeap(right_child_index, index);
    }
    downHeap(right_child_index);
  }
}

void insertItem(int key) {
  // heap_size 증가
  heap_size++;

  // 해당 위치에 원소 추가
  heap[heap_size] = key;

  // upHeap 수행
  upHeap(heap_size);
}

int removeMax(void) {
  // 마지막 원소를 루트로 가져옴 (루트 삭제)
  int removed_key = heap[1];
  heap[1] = heap[heap_size];

  // heap_size 감소
  heap_size--;

  // downHeap 을 통해 루트를 적절한 위치로 이동
  downHeap(1);

  return removed_key;
}

void printHeap(void) {
  for (int i = 1; i <= heap_size; i++) {
    printf(" %d", heap[i]);
  }
  printf("\n");
}

int main(void) {
  char command;
  int key;

  while (true) {
    scanf(" %c", &command);

    if (command == 'i') {
      scanf(" %d", &key);
      insertItem(key);
      printf("0\n");
    } else if (command == 'd') {
      int removed_key = removeMax();
      printf("%d\n", removed_key);
    } else if (command == 'p') {
      printHeap();
    } else if (command == 'q') {
      break;
    } else {
      printf("invalid command");
      exit(EXIT_FAILURE);
    }
  }

  return EXIT_SUCCESS;
}
