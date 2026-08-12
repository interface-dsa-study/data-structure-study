#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

typedef struct List {
  Node *head;
  Node *tail;
  int size;
} List;

typedef struct PartitionResult {
  List *list1;
  List *list2;
} PartitionResult;

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

Node *createNode(int data) {
  Node *node = malloc(sizeof(*node));
  if (node == NULL) {
    exit(EXIT_FAILURE);
  }
  node->data = data;
  node->next = NULL;
  return node;
}

void addList(List *list, int data) {
  Node *node = createNode(data);

  if (list->size == 0) {
    list->head = node;
    list->tail = node;
    list->size++;
    return;
  }

  list->tail->next = node;
  list->tail = node;
  list->size++;
}

void addNode(List *list, Node *node) {
  node->next = NULL;

  if (list->size == 0) {
    list->head = node;
    list->tail = node;
    list->size++;
    return;
  }

  list->tail->next = node;
  list->tail = node;
  list->size++;
}

void destroyList(List *list) {
  if (list == NULL) {
    return;
  }

  Node *node = list->head;
  while (node != NULL) {
    Node *next_node = node->next;
    free(node);
    node = next_node;
  }
  free(list);
}

PartitionResult partition(List *list, int size) {
  PartitionResult partition_result;

  partition_result.list1 = createList();
  partition_result.list2 = createList();

  Node *current_node = list->head;

  for (int i = 0; i < size - 1; i++) {
    current_node = current_node->next;
  }

  // list1 구성
  partition_result.list1->head = list->head;
  partition_result.list1->tail = current_node;
  partition_result.list1->size = size;

  // list2 구성
  partition_result.list2->head = current_node->next;
  partition_result.list2->tail = list->tail;
  partition_result.list2->size = list->size - size;

  current_node->next = NULL;
  return partition_result;
}

List *merge(List *list1, List *list2) {
  List *result_list = createList();
  Node *current_node1 = list1->head;
  Node *current_node2 = list2->head;

  while (current_node1 != NULL && current_node2 != NULL) {
    if (current_node1->data <= current_node2->data) {
      Node *next_node = current_node1->next;
      addNode(result_list, current_node1);
      current_node1 = next_node;
    } else {
      Node *next_node = current_node2->next;
      addNode(result_list, current_node2);
      current_node2 = next_node;
    }
  }

  while (current_node1 != NULL) {
    Node *next_node = current_node1->next;
    addNode(result_list, current_node1);
    current_node1 = next_node;
  }

  while (current_node2 != NULL) {
    Node *next_node = current_node2->next;
    addNode(result_list, current_node2);
    current_node2 = next_node;
  }

  return result_list;
}

List *mergeSort(List *list) {
  if (list->size <= 1) {
    return list;
  }

  PartitionResult partition_result = partition(list, list->size / 2);

  List *left_list = mergeSort(partition_result.list1);
  List *right_list = mergeSort(partition_result.list2);
  List *result_list = merge(left_list, right_list);

  free(left_list);
  free(right_list);
  free(list);
  return result_list;
}

void printList(List *list) {
  Node *current_node = list->head;
  while (current_node != NULL) {
    printf(" %d", current_node->data);
    current_node = current_node->next;
  }
  printf("\n");
}

int main(void) {
  int size;
  scanf("%d", &size);
  List *list = createList();

  for (int i = 0; i < size; i++) {
    int data;
    scanf("%d", &data);
    addList(list, data);
  }

  list = mergeSort(list);

  printList(list);

  destroyList(list);
  return EXIT_SUCCESS;
}
