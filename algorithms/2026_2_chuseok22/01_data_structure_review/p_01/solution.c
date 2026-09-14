#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
  char element;
  struct Node *prev;
  struct Node *next;
} Node;

typedef struct List {
  Node *header;
  Node *trailer;
  int size;
} List;

Node *createNode(char element) {
  Node *node = malloc(sizeof(*node));
  if (node == NULL) {
    exit(EXIT_FAILURE);
  }
  node->element = element;
  node->prev = NULL;
  node->next = NULL;
  return node;
}

List *createList(void) {
  List *list = malloc(sizeof(*list));
  if (list == NULL) {
    exit(EXIT_FAILURE);
  }
  list->header = createNode('\0');
  list->trailer = createNode('\0');

  list->header->next = list->trailer;
  list->trailer->prev = list->header;

  list->size = 0;
  return list;
}

Node *getNode(List *list, int rank) {
  Node *current_node = list->header;
  for (int index = 0; index < rank; index++) {
    current_node = current_node->next;
  }
  return current_node;
}

void get(List *list, int rank) {
  Node *target_node = getNode(list, rank);
  if (target_node == list->header || target_node == list->trailer) {
    printf("invalid position\n");
    return;
  }
  printf("%c\n", target_node->element);
}

void add(List *list, int rank, char element) {
  if (rank > list->size + 1) {
    printf("invalid position\n");
    return;
  }
  Node *new_node = createNode(element);
  Node *target_node = getNode(list, rank);

  if (rank == 1) {
    new_node->prev = list->header;
    new_node->next = target_node;

    list->header->next = new_node;
    target_node->prev = new_node;

    list->size++;
    return;
  }
  new_node->prev = target_node->prev;
  new_node->next = target_node;

  target_node->prev->next = new_node;
  target_node->prev = new_node;

  list->size++;
}

void deleteNode(List *list, int rank) {
  if (rank > list->size) {
    printf("invalid position\n");
    return;
  }

  Node *target_node = getNode(list, rank);
  Node *previous_node = target_node->prev;
  Node *next_node = target_node->next;

  previous_node->next = next_node;
  next_node->prev = previous_node;
  free(target_node);
  list->size--;
}

void print(List *list) {
  if (list == NULL) {
    return;
  }

  Node *current_node = list->header->next;
  while (current_node != NULL && current_node != list->trailer) {
    printf("%c", current_node->element);
    current_node = current_node->next;
  }
  printf("\n");
}

void destroyList(List *list) {
  if (list == NULL) {
    return;
  }
  Node *current_node = list->header;
  while (current_node != NULL) {
    Node *next_node = current_node->next;
    free(current_node);
    current_node = next_node;
  }
  free(list);
}

int main(void) {
  int count, rank;
  char operator, element;
  List *list = createList();

  scanf("%d", &count);
  for (int i = 0; i < count; i++) {
    scanf(" %c", &operator);

    if (operator == 'A') {
      scanf("%d %c", &rank, &element);
      add(list, rank, element);
    } else if (operator == 'D') {
      scanf("%d", &rank);
      deleteNode(list, rank);
    } else if (operator == 'G') {
      scanf("%d", &rank);
      get(list, rank);
    } else if (operator == 'P') {
      print(list);
    } else {
      exit(EXIT_FAILURE);
    }
  }
  destroyList(list);
  return EXIT_SUCCESS;
}
