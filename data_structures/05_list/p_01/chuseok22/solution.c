#include <stdlib.h>
#include <stdio.h>
typedef struct Node {
  int coef;
  int exp;
  struct Node *next;
} Node;

typedef struct List {
  Node *header;
  int size;
} List;

// 새로운 노드를 동적으로 생성
Node *create_node(int coef, int exp) {
  Node *node = malloc(sizeof(Node));
  if (node == NULL) {
    fprintf(stderr, "메모리 할당 실패");
    exit(EXIT_FAILURE);
  }
  node->coef = coef;
  node->exp = exp;
  node->next = NULL;

  return node;
}

// 새로운 빈 리스트 생성
List *create_list() {
  List *list = malloc(sizeof(List));
  if (list == NULL) {
    fprintf(stderr, "메모리 할당에 실패했습니다.\n");
    exit(EXIT_FAILURE);
  }
  Node *header = create_node(0, 0);
  list->header = header;
  list->size = 0;
  return list;
}

Node *append_node(List *list, Node *tail_node, int coef, int exp) {
  // 계수가 0인 경우
  if (coef == 0) {
    return tail_node;
  }

  Node *new_node = create_node(coef, exp);
  tail_node->next = new_node;
  list->size++;
  return new_node;
}

List *read_polynomial(void) {
  List *polynomial_list = create_list();
  Node *tail_node = polynomial_list->header;
  int term_count, coef, exp;
  scanf("%d", &term_count);

  for (int i = 0; i < term_count; i++) {
    scanf("%d %d", &coef, &exp);
    tail_node = append_node(polynomial_list, tail_node, coef, exp);
  }
  return polynomial_list;
}

List *add_polynomial_list(List *list1, List *list2) {
  List *result_list = create_list();
  Node *result_tail_node = result_list->header;

  Node *first_current_node = list1->header->next;
  Node *second_current_node = list2->header->next;

  while (first_current_node != NULL && second_current_node != NULL) {
    if (first_current_node->exp > second_current_node->exp) {
      result_tail_node = append_node(
        result_list,
        result_tail_node,
        first_current_node->coef,
        first_current_node->exp
      );
      first_current_node = first_current_node->next;
    } else if (first_current_node->exp < second_current_node->exp) {
      result_tail_node = append_node(
        result_list,
        result_tail_node,
        second_current_node->coef,
        second_current_node->exp
      );
      second_current_node = second_current_node->next;
    } else if (first_current_node->exp == second_current_node->exp) {
      int coef_sum = first_current_node->coef + second_current_node->coef;

      result_tail_node = append_node(
        result_list,
        result_tail_node,
        coef_sum,
        first_current_node->exp
      );
      first_current_node = first_current_node->next;
      second_current_node = second_current_node->next;
    }
  }

  // 첫번째 다항식 남은 항 추가
  while (first_current_node != NULL) {
    result_tail_node = append_node(
      result_list,
      result_tail_node,
      first_current_node->coef,
      first_current_node->exp
    );
    first_current_node = first_current_node->next;
  }

  // 두번째 다항식 남은 항 추가
  while (second_current_node != NULL) {
    result_tail_node = append_node(
      result_list,
      result_tail_node,
      second_current_node->coef,
      second_current_node->exp
    );
    second_current_node = second_current_node->next;
  }

  return result_list;
}

// List 출력
void print_polynomial(List *list) {
  Node *current_node = list->header->next;
  while (current_node != NULL) {
    printf(" %d %d", current_node->coef, current_node->exp);
    current_node = current_node->next;
  }
}

// List 메모리 해제
void free_list(List *list) {
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
  List *first_polynomial = read_polynomial();
  List *second_polynomial = read_polynomial();

  List *result_polynomial = add_polynomial_list(first_polynomial, second_polynomial);
  print_polynomial(result_polynomial);

  free_list(first_polynomial);
  free_list(second_polynomial);
  free(result_polynomial);
}
