#include <stdio.h>
int heap[101];
int heap_size = 0;

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

/**
 * 본인 i
 * 부모 i / 2
 * 왼쪽 자식 i * 2
 * 오른쪽 자식 i * 2 + 1
 */
void downHeap(int index) {
  int left_child_index = index * 2;
  int right_child_index = index * 2 + 1;

  // 왼쪽 자식이 없으면 종료
  if (left_child_index > heap_size) {
    return;
  }

  // 왼쪽 자식이 더 크다고 가정
  int large_child_index = left_child_index;

  // 오른쪽 자식이 존재하며, 더 큰 경우
  if (right_child_index <= heap_size && heap[right_child_index] > heap[left_child_index]) {
    large_child_index = right_child_index;
  }

  // 부모가 더 큰 경우 swap 하지 않고 종료
  if (heap[index] >= heap[large_child_index]) {
    return;
  }
  swap(&heap[index], &heap[large_child_index]);
  downHeap(large_child_index);
}

void buildHeap(void) {
  // 마지막 내부 노드부터 index 1까지 처리
  int last_inner_node_index = heap_size / 2;

  for (int i = last_inner_node_index; i >= 1; i--) {
    downHeap(i);
  }
}

void printHeap(void) {
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

  buildHeap();
  printHeap();
}
