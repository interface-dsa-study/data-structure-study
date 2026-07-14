#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  int value;
  struct Node *previous_node;
  struct Node *next_node;
} Node;

typedef struct Dequeue {
  Node *front_node;
  Node *rear_node;
} Dequeue;

Node *create_node(int value) {
  Node *node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  node->previous_node = NULL;
  node->next_node = NULL;
  node->value = value;
  return node;
}

Dequeue *create_dequeue(void) {
  Dequeue *dequeue = malloc(sizeof(*dequeue));
  if (dequeue == NULL) {
    exit(EXIT_FAILURE);
  }
  dequeue->front_node = NULL;
  dequeue->rear_node = NULL;
  return dequeue;
}

void destroy_dequeue(Dequeue *dequeue) {
  if (dequeue == NULL) {
    return;
  }

  Node *current_node = dequeue->front_node;

  while (current_node != NULL) {
    Node *next_node = current_node->next_node;
    free(current_node);
    current_node = next_node;
  }
  free(dequeue);
}

bool is_empty(Dequeue *dequeue) {
  return dequeue->front_node == NULL && dequeue->rear_node == NULL;
}

void add_front(Dequeue *dequeue, int value) {
  Node *new_node = create_node(value);

  if (is_empty(dequeue)) {
    dequeue->front_node = new_node;
    dequeue->rear_node = new_node;
    return;
  }

  new_node->next_node = dequeue->front_node;
  dequeue->front_node->previous_node = new_node;

  dequeue->front_node = new_node;
}

void add_rear(Dequeue *dequeue, int value) {
  Node *new_node = create_node(value);

  if (is_empty(dequeue)) {
    dequeue->front_node = new_node;
    dequeue->rear_node = new_node;
    return;
  }

  new_node->previous_node = dequeue->rear_node;
  dequeue->rear_node->next_node = new_node;

  dequeue->rear_node = new_node;
}

int delete_front(Dequeue *dequeue) {
  if (is_empty(dequeue)) {
    printf("underflow\n");
    destroy_dequeue(dequeue);
    exit(EXIT_SUCCESS);
  }

  Node *deleted_node = dequeue->front_node;
  int deleted_value = deleted_node->value;

  if (dequeue->front_node == dequeue->rear_node) {
    dequeue->front_node = NULL;
    dequeue->rear_node = NULL;
  } else {
    dequeue->front_node = dequeue->front_node->next_node;
    dequeue->front_node->previous_node = NULL;
  }

  free(deleted_node);
  return deleted_value;
}

int delete_rear(Dequeue *dequeue) {
  if (is_empty(dequeue)) {
    printf("underflow\n");
    destroy_dequeue(dequeue);
    exit(EXIT_SUCCESS);
  }

  Node *deleted_node = dequeue->rear_node;
  int deleted_value = deleted_node->value;

  if (dequeue->front_node == dequeue->rear_node) {
    dequeue->front_node = NULL;
    dequeue->rear_node = NULL;
  } else {
    dequeue->rear_node = dequeue->rear_node->previous_node;
    dequeue->rear_node->next_node = NULL;
  }

  free(deleted_node);
  return deleted_value;
}

void print(Dequeue *dequeue) {
  Node *current_node = dequeue->front_node;

  while (current_node != NULL) {
    printf(" %d", current_node->value);
    current_node = current_node->next_node;
  }
  printf("\n");
}

int main(void) {
  int operation_count = 0, value;
  char operation_type[3];
  Dequeue *dequeue = create_dequeue();

  scanf("%d", &operation_count);

  for (int i = 0; i < operation_count; i++) {
    scanf("%s", operation_type);

    if (strcmp(operation_type, "AF") == 0) {
      scanf(" %d", &value);
      add_front(dequeue, value);
    } else if (strcmp(operation_type, "AR") == 0) {
      scanf(" %d", &value);
      add_rear(dequeue, value);
    } else if (strcmp(operation_type, "DF") == 0) {
      delete_front(dequeue);
    } else if (strcmp(operation_type, "DR") == 0) {
      delete_rear(dequeue);
    } else if (strcmp(operation_type, "P") == 0) {
      print(dequeue);
    }
  }
  destroy_dequeue(dequeue);
}
