#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
  int value;
  struct Node *next;
} Node;

typedef struct List {
  Node *head;
  Node *tail;
  int size;
} List;

typedef struct PartitionList {
  List *list1;
  List *list2;
} PartitionList;

Node *createNode(int value) {
  Node *node = malloc(sizeof(*node));
  if (node == NULL) {
    exit(EXIT_FAILURE);
  }

  node->value = value;
  node->next = NULL;
  return node;
}

List *createList(void) {
  List *list = malloc(sizeof(*list));
  if (list == NULL) {
    exit(EXIT_FAILURE);
  }

  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

void addNode(List *list, Node *node) {
  // List 가 비어있는 경우
  if (list->size == 0) {
    list->head = node;
    list->tail = node;
    list->size++;
    return;
  }

  // List 가 비어있지 않은 경우
  list->tail->next = node;
  list->tail = node;
  list->size++;
}

void destroyList(List *list) {
  if (list->size == 0) {
    free(list);
    return;
  }
  Node *current_node = list->head;
  while (current_node != NULL) {
    Node *next_node = current_node->next;
    free(current_node);
    current_node = next_node;
  }
  free(list);
}

PartitionList partition(List *list, int k) {
  PartitionList partition_list;
  partition_list.list1 = createList();
  partition_list.list2 = createList();

  // 부리스트 L2 헤더설정
  Node *partition_list2_head = list->head;
  for (int i = 0; i < k; i++) {
    partition_list2_head = partition_list2_head->next;
  }

  // 부리스트 L1 설정
  partition_list.list1->head = list->head;
  partition_list.list1->size = k;
  Node *list1_last_node = partition_list.list1->head;
  for (int i = 0; i < k - 1; i++) {
    list1_last_node = list1_last_node->next;
  }
  // 부리스트 L1 마지막 node->next NULL 설정
  list1_last_node->next = NULL;
  partition_list.list1->tail = list1_last_node;

  partition_list.list2->head = partition_list2_head;
  partition_list.list2->tail = list->tail;
  partition_list.list2->size = list->size - k;

  return partition_list;
}

List *merge(List *list1, List *list2) {
  // list1, list2 순차적으로 비교하여 합병 진행
  List *list = createList();
  Node *list1_node = list1->head;
  Node *list2_node = list2->head;

  // list1, list2 모두 NULL 이 아닌경우
  while (list1_node != NULL && list2_node != NULL) {
    if (list1_node->value <= list2_node->value) {
      // list1 원소가 작은 경우
      addNode(list, list1_node);
      list1_node = list1_node->next;
    } else {
      // list2 원소가 작은 경우
      addNode(list, list2_node);
      list2_node = list2_node->next;
    }
  }

  // list1 원소가 남아있는 경우
  while (list1_node != NULL) {
    addNode(list, list1_node);
    list1_node = list1_node->next;
  }

  // list2 원소가 남아있는 경우
  while (list2_node != NULL) {
    addNode(list, list2_node);
    list2_node = list2_node->next;
  }

  // list1, list2 동적 메모리 해제
  free(list1);
  free(list2);

  // 합병된 list 반환
  return list;
}

List *mergeSort(List *list) {
  // list 크기가 1보다 작거나 같으면 반환
  if (list->size <= 1) {
    return list;
  }

  // 두 개의 subList 분리
  PartitionList partition_list = partition(list, list->size / 2);

  // 기존 리스트 동적메모리 해제
  free(list);

  // 부리스트 재귀 호출
  partition_list.list1 = mergeSort(partition_list.list1);
  partition_list.list2 = mergeSort(partition_list.list2);

  // 병합 진행
  return merge(partition_list.list1, partition_list.list2);
}

void printList(List *list) {
  Node *current_node = list->head;

  while (current_node != NULL) {
    printf(" %d", current_node->value);
    current_node = current_node->next;
  }
}

int main(void) {
  int n;
  scanf("%d", &n);

  List *list = createList();

  for (int i = 0; i < n; i++) {
    int new_value;
    scanf(" %d", &new_value);
    Node *new_node = createNode(new_value);
    addNode(list, new_node);
  }

  list = mergeSort(list);

  printList(list);

  destroyList(list);
}
