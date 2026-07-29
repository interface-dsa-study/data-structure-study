#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

int n = 0; // 힙 크기
int heap[MAX_HEAP_SIZE];

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

  // 왼쪽 자식과 비교
  if (heap[index] < heap[index * 2]) {
    swap(&heap[index], &heap[index * 2]);
    downHeap(index * 2);
  }

  // 오른쪽 자식과 비교
  if (heap[index] < heap[index * 2 + 1]) {
    swap(&heap[index], &heap[index * 2 + 1]);
    downHeap(index * 2 + 1);
  }
}

void insertItem(int key) {
  n++;
  heap[n] = key;
  upHeap(n);
  printf("0\n");
}

int removeMax(void) {
  int max_integer = heap[1];

  // 루트와 마지막 원소 swap
  heap[1] = heap[n];

  // heap 사이즈 감소
  n--;

  downHeap(1);

  return max_integer;
}

void printHeap(void) {
  for (int i = 1; i <= n; i++) {
    printf(" %d", heap[i]);
  }
  printf("\n");
}

int main(void) {
  char operator;
  int key;

  while (true) {
    scanf(" %c", &operator);
    if (operator == 'i') {
      scanf(" %d", &key);
      insertItem(key);
    } else if (operator == 'd') {
      int remove_element = removeMax();
      printf("%d\n", remove_element);
    } else if (operator == 'p') {
      printHeap();
    } else if (operator == 'q') {
      return 0;
    } else {
      exit(EXIT_FAILURE);
    }
  }
}
