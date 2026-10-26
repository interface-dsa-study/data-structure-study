#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int element;
  struct Node *next;
} Node;

typedef struct List {
  Node *head;
  Node *tail;
  int size;
} List;

// Node 생성
Node *createNode(int element) {
  Node *node = malloc(sizeof(*node));
  if (node == NULL) {
    exit(EXIT_FAILURE);
  }

  node->element = element;
  node->next = NULL;
  return node;
}

// List 생성
List *createList(void) {
  List *list = malloc(sizeof(*list));
  if (list == NULL) {
    exit(EXIT_FAILURE);
  }
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}

void addLast(List *list, int element) {
  // 리스트 마지막 삽입

  // 새로운 노드 생성
  Node *new_node = createNode(element);

  if (list->size == 0) {
    // 리스트가 비어있는 경우
    list->head = new_node;
    list->tail = new_node;
    list->size++;
    return;
  }

  list->tail->next = new_node;
  list->tail = new_node;
  list->size++;
}

int rFAE(int *array, int key, int left, int right) {
  if (left > right) {
    // 탐색 실패
    return -1;
  }

  // 중앙 인덱스
  int mid = (left + right) / 2;

  if (key == array[mid]) {
    // key 를 찾은 경우 반환 (인덱스)
    return mid;
  } else if (key < array[mid]) {
    // key 가 더 작은 경우
    return rFAE(array, key, left, mid - 1);
  } else if (key > array[mid]) {
    // key 가 더 큰 경우
    return rFAE(array, key, mid + 1, right);
  }
}

// 배열, key, 배열size 를 인자로 받음
List *findAllElements(int *array, int key, int size) {
  int target_index = rFAE(array, key, 0, size - 1); // key에 해당하는 index 찾기

  List *list = createList();

  if (target_index == -1) {
    // 못찾은 경우
    return NULL;
  }

  while (target_index >= 0 && array[target_index] == key) {
    target_index--;
  }
  target_index++;
  while (target_index < size && array[target_index] == key) {
    addLast(list, array[target_index]);
    target_index++;
  }

  return list;
}

void printList(List *list) {
  Node *current_node = list->head;
  while (current_node != NULL) {
    printf(" %d", current_node->element);
  }
}

void destroyList(List *list) {
  Node *current_node = list->head;
  while (current_node != NULL) {
    Node *next_node = current_node->next;
    free(current_node);
    current_node = next_node;
  }
  free(list);
}

int main(void) {
  int n, key;
  scanf("%d %d", &n, &key);

  int *array = malloc(sizeof(*array) * n);
  if (array == NULL) {
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n; i++) {
    scanf("%d", &array[i]);
  }

  List *list = findAllElements(array, key, n);

  printList(list);

  destroyList(list);
  free(array);
}
