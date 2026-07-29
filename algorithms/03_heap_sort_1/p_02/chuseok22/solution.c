#include <stdio.h>

#define MAX_HEAP_SIZE 100

int heap[MAX_HEAP_SIZE];
int n = 0; // 힙 크기

void swap(int *value1, int *value2) {
  int tmp = *value1;
  *value1 = *value2;
  *value2 = tmp;
}

void upHeap(int index) {
  /**
   * 현재 인덱스: i
   * 부모 인덱스: i/2
   * 왼쪽 자식: 2 * i
   * 오른쪽 자식: 2 * i + 1
   */

  // 루트 도달 시 종료
  if (index <= 1) {
    return;
  }

  // 자식이 부모보다 큰 경우 swap
  if (heap[index] > heap[index / 2]) {
    swap(&heap[index], &heap[index / 2]);
  }

  upHeap(index / 2);
}

void downHeap(int index) {
  if (index >= n) {
    return;
  }

  // 자식들 먼저 비교
  if (heap[index * 2] > heap[index * 2 + 1]) {
    // 왼쪽 자식과 비교
    if (heap[index] < heap[index * 2]) {
      swap(&heap[index], &heap[index * 2]);
      downHeap(index * 2);
    }
  } else {
    // 오른쪽 자식과 비교
    if (heap[index] < heap[index * 2 + 1]) {
      swap(&heap[index], &heap[index * 2 + 1]);
      downHeap(index * 2 + 1);
    }
  }
}

void printHeap(void) {
  for (int i = 1; i <= n; i++) {
    printf(" %d", heap[i]);
  }
  printf("\n");
}

void rBuildHeap(int i) {
  if (i > n) {
    return;
  }
  rBuildHeap(2 * i);
  rBuildHeap(2 * i + 1);
  downHeap(i);
}

void buildHeap(void) {
  for (int i = n / 2; i >= 1; i--) {
    downHeap(i);
  }
}

int main(void) {
  scanf("%d", &n);

  for (int i = 1; i <= n; i++) {
    int element;
    scanf("%d", &element);
    heap[i] = element;
  }

  // rBuildHeap(1);
  buildHeap();

  printHeap();

  return 0;
}
