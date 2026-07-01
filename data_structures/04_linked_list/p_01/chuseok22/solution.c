#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  struct Node *previous;
  char element;
  struct Node *next;
} Node;

typedef struct LinkedList {
  Node *header;
  Node *trailer;
  int size;
} LinkedList;

/**
 * 새로운 노드를 동적 할당
 */
Node *create_node(char element) {
  Node *new_node;

  new_node = malloc(sizeof(Node));
  if (new_node == NULL) {
    fprintf(stderr, "메모리 할당 실패");
    exit(EXIT_FAILURE);
  }

  new_node->previous = NULL;
  new_node->next = NULL;
  new_node->element = element;

  return new_node;
}

/**
 * 빈 리스트 생성
 */
LinkedList *create_linked_list(void) {
  LinkedList *linked_list;
  linked_list = malloc(sizeof(LinkedList));

  if (linked_list == NULL) {
    fprintf(stderr, "메모리 할당 실패");
    exit(EXIT_FAILURE);
  }

  linked_list->header = create_node('\0');
  linked_list->trailer = create_node('\0');

  linked_list->header->next = linked_list->trailer;
  linked_list->trailer->previous = linked_list->header;

  linked_list->size = 0;

  return linked_list;
}

/**
 * 지정한 순위의 노드 반환
 */
Node *get_node(LinkedList *linked_list, int rank) {
  Node *current_node;
  int current_rank;

  current_node = linked_list->header->next;
  current_rank = 1;

  while (current_rank < rank) {
    current_node = current_node->next;
    current_rank++;
  }

  return current_node;
}

void add(LinkedList *linked_list, int rank, char element) {
  Node *previous_node;
  Node *next_node;
  Node *new_node;

  if (rank < 1 || rank > linked_list->size + 1) {
    fprintf(stdout, "invalid position\n");
    return;
  }

  // 마지막 위치에 add 하는 경우 next_node = trailer
  if (rank == linked_list->size + 1) {
    next_node = linked_list->trailer;
  } else {
    next_node = get_node(linked_list, rank);
  }

  previous_node = next_node->previous;
  new_node = create_node(element);

  new_node->previous = previous_node;
  new_node->next = next_node;

  previous_node->next = new_node;
  next_node->previous = new_node;

  linked_list->size++;
}

void delete(LinkedList *linked_list, int rank) {
  Node *target_node;
  Node *previous_node;
  Node *next_node;

  if (rank < 1 || rank > linked_list->size) {
    fprintf(stdout, "invalid position\n");
    return;
  }

  target_node = get_node(linked_list, rank);
  previous_node = target_node->previous;
  next_node = target_node->next;

  previous_node->next = next_node;
  next_node->previous = previous_node;
  free(target_node);

  linked_list->size--;
}

void get(LinkedList *linked_list, int rank) {
  if (rank < 1 || rank > linked_list->size) {
    fprintf(stdout, "invalid position\n");
    return;
  }
  Node *target_node = get_node(linked_list, rank);
  fprintf(stdout, "%c\n", target_node->element);
}

void print(LinkedList *linked_list) {
  Node *current_node = linked_list->header->next;
  while (current_node != linked_list->trailer) {
    fprintf(stdout, "%c", current_node->element);
    current_node = current_node->next;
  }
  fprintf(stdout, "\n");
}

void destroy_linked_list(LinkedList *linked_list) {
  if (linked_list == NULL) {
    return;
  }
  Node *current_node = linked_list->header;

  while (current_node != NULL) {
    Node *next_node = current_node->next;
    free(current_node);
    current_node = next_node;
  }
  free(linked_list);
}

int main(void) {
  int count, rank;
  char function_type, element;
  LinkedList *linked_list = create_linked_list();

  scanf("%d", &count);

  for (int i = 0; i < count; i++) {
    scanf(" %c", &function_type);
    if (function_type == 'A') {
      scanf("%d %c", &rank, &element);
      add(linked_list, rank, element);
    } else if (function_type == 'D') {
      scanf("%d", &rank);
      delete(linked_list, rank);
    } else if (function_type == 'G') {
      scanf("%d", &rank);
      get(linked_list, rank);
    } else if (function_type == 'P') {
      print(linked_list);
    } else {
      fprintf(stderr, "invalid function type");
      destroy_linked_list(linked_list);
      return EXIT_FAILURE;
    }
  }

  destroy_linked_list(linked_list);
  return EXIT_SUCCESS;
}
