#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
  int element;
  struct Node *next;
} Node;

typedef struct List {
  Node *head;
  Node *tail;
} List;

typedef struct PartitionList {
  List list1;
  List list2;
} PartitionList;

Node *createNode(int element) {
  Node *node = malloc(sizeof(*node));
  if (node == NULL) {
    exit(EXIT_FAILURE);
  }
  node->element = element;
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
  return list;
}

void addNode(List *list, Node *node) {
  // 비어있는 경우
  if (list->head == list->tail) {
    list->head = node;
    list->tail = node;
    return;
  }

  list->tail->next = node;
  list->tail = node;
}

PartitionList partition(List *list, int k) {
  PartitionList partition_list;

  // 부리스트 head 설정
  Node *head1 = list->head;
  Node *head2 = list->head;
  for (int i = 0; i < k; i++) {
    head2 = head2->next;
  }

  // 부리스트 tail 설정
  Node *tail1 = list->head;
  for (int i = 0; i < k - 1; i++) {
    tail1 = tail1->next;
  }
  tail1->next = NULL;

  Node *tail2 = list->tail;

  partition_list.list1.head = head1;
  partition_list.list1.tail = tail1;
  partition_list.list2.head = head2;
  partition_list.list2.tail = tail2;

  free(list);
  return partition_list;
}

List *merge(List *list1, List *list2) {
  List *merged_list = createList();
  Node *node1 = list1->head;
  Node *node2 = list2->head;

  while (node1 != NULL && node2 != NULL) {
    if (node1->element < node2->element) {
      addNode(merged_list, node1);
      node1 = node1->next;
    } else {
      addNode(merged_list, node2);
      node2 = node2->next;
    }
  }

  while (node1 != NULL) {
    addNode(merged_list, node1);
    node1 = node1->next;
  }

  while (node2 != NULL) {
    addNode(merged_list, node2);
    node2 = node2->next;
  }

  free(list1);
  free(list2);
  return merged_list;
}

List *mergeSort(List *list) {
  // list.size == 1 이면 종료
  if (list->head == list->tail) {
    return list;
  }
  PartitionList partition_list = partition(list, )
}

int main(void) {
  int n;
  scanf("%d", &n);
}
