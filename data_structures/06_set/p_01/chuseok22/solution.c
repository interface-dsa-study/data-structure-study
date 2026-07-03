#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
  int value;
  struct Node *next;
} Node;

Node *create_node(int value) {
  Node *new_node = malloc(sizeof(*new_node));
  if (new_node == NULL) {
    fprintf(stderr, "메모리 할당 실패");
    exit(EXIT_FAILURE);
  }
  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}

Node *add_value_at_tail(Node *tail_node, int value) {
  Node *new_node = create_node(value);
  tail_node->next = new_node;
  return new_node;
}

Node *create_set_from_input(int set_size) {
  Node *head_node = NULL;
  Node *current_node = NULL;

  for (int i = 0; i < set_size; i++) {
    int value;
    scanf("%d", &value);
    Node *new_node = create_node(value);
    if (head_node == NULL) {
      head_node = new_node;
      current_node = new_node;
      continue;
    }
    current_node->next = new_node;
    current_node = new_node;
  }

  return head_node;
}

int subset(Node *set_a_header_node, Node *set_b_header_node) {
  Node *current_a_node = set_a_header_node;
  Node *current_b_node = set_b_header_node;

  while (current_a_node != NULL) {
    // B 원소가 더 작은 경우 PASS
    while (
      current_b_node != NULL &&
      current_b_node->value < current_a_node->value
    ) {
      current_b_node = current_b_node->next;
    }

    // B 원소를 모두 확인했는데 A 원소가 남은 경우
    if (current_b_node == NULL) {
      return current_a_node->value;
    }

    // A 원소가 B 원소보다 작은경우
    if (current_a_node->value < current_b_node->value) {
      return current_a_node->value;
    }

    // 두 원소 값이 같은 경우
    current_a_node = current_a_node->next;
    current_b_node = current_b_node->next;
  }

  return 0;
}

void free_node_concurrency(Node *head_node) {
  Node *current_node = head_node;
  Node *next_node = NULL;

  while (current_node->next != NULL) {
    next_node = current_node->next;
    free(current_node);
    current_node = next_node;
  }
}

int main(void) {
  int set_a_size, set_b_size, result;

  scanf("%d", &set_a_size);
  Node *set_a_head_node = create_node(set_a_size);

  scanf("%d", &set_b_size);
  Node *set_b_head_node = create_node(set_b_size);

  result = subset(set_a_head_node, set_b_head_node);
  printf("%d", result);
  free(set_a_head_node);
  free(set_b_head_node);
}
